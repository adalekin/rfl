/*
 * Rightway Support Libraries.
 * Copyright (C) 2009  Alexey Dalekin
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef __RIGHTWAY_SMTP_DETAIL_ASIO_MAILBOX_HPP__
#define __RIGHTWAY_SMTP_DETAIL_ASIO_MAILBOX_HPP__

#include <rightway/smtp/mailbox.hpp>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#include <vector>
#include <iostream>
#include <sstream>

#include "base64.hpp"

namespace rightway { namespace system {

template<>
class pimpl<rightway::smtp::mailbox>::implementation
{
    static const time_t receive_timeout_ = 5;
    static const time_t send_timeout_    = 5;

public:
    implementation()
        : initialized_(false)
        , socket_(INVALID_SOCKET)
    {
    }

    ~implementation()
    {
        error_code error;
        uninitialize(error);
    }

private:
    void initialize(error_code & ec)
    {
        ec = success;

        if (is_initialized())
        {
            return;
        }

        // Initialize WinSock
        WORD ver = MAKEWORD(2,2);    

        if (::WSAStartup(ver, &wsa_data_) != NO_ERROR)
        {
            ec = rightway::smtp::error::wsa_startup;
            return;
        }

        if (LOBYTE( wsa_data_.wVersion ) != 2 || HIBYTE( wsa_data_.wVersion ) != 2 ) 
        {
            ec = rightway::smtp::error::wsa_version;

            ::WSACleanup();
            return;
        }

        initialized_ = true;
    }

    void uninitialize(error_code & ec)
    {
        ec = success;

        if (is_initialized())
        {
            if (is_connected())
            {
                disconnect(ec);
            }

            ::WSACleanup();
        }

        initialized_ = false;
    }

    bool is_initialized() const
    {
        return initialized_;
    }

public:
    void connect(const std::string & server, std::size_t port, error_code & ec)
    {
        ec = success;

        if (!is_initialized())
        {
            initialize(ec);
        }

        if (ec)
        {
            return;
        }

        hostent* hp;
        if (::inet_addr(server.c_str()) == INADDR_NONE)
        {
            hp = ::gethostbyname(server.c_str());
        }
        else
        {
            unsigned int ia = inet_addr(server.c_str());
            hp = ::gethostbyaddr((char*)&ia, sizeof(ia), AF_INET);
        }

        if (hp == NULL)
        {
            ec = rightway::smtp::error::not_resolved;
            return;
        }

        if( (socket_ = ::socket(PF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
        {
            ec = rightway::smtp::error::invalid_socket;
            return;
        }

        sockaddr_in sock_addr;
        sock_addr.sin_family      = AF_INET;
        sock_addr.sin_port        = ::htons(port);;
        sock_addr.sin_addr.s_addr = *((unsigned long*)hp->h_addr);

        if (::connect(socket_, (sockaddr*) &sock_addr, sizeof(sock_addr)) == SOCKET_ERROR)
        {
            ec = rightway::smtp::error::not_connected;
            return;
        }

        std::string response;

        response = receive_buffer(ec);

        if (ec)
        {
            return;
        }

        send_buffer("HELO rightway\r\n", ec);

        if (ec)
        {
            return;
        }

        response = receive_buffer(ec);

        if (ec)
        {
            return;
        }

        if (!check_response(response, 250))
        {
            ec = rightway::smtp::error::not_supported;
            return;
        }
    }

    bool is_connected() const
    {
        return socket_ != INVALID_SOCKET;
    }

    void disconnect(error_code & ec)
    {
        ec = success;

        if (!is_connected())
        {
            ec = rightway::smtp::error::not_connected;
            return;
        }

        ::closesocket(socket_);
    }

    void auth(const std::string & username, const std::string & pass, error_code & ec)
    {
        ec = success;

        if (!is_connected())
        {
            ec = rightway::smtp::error::not_connected;
            return;
        }

        send_buffer("AUTH LOGIN\r\n", ec);

        if (ec)
        {
            return;
        }

        std::string response = receive_buffer(ec);

        if (ec)
        {
            return;
        }

        if (!check_response(response, 334))
        {
            ec = rightway::smtp::error::not_supported;
            return;
        }


        send_buffer(rightway::smtp::detail::base64::encode_string(username) + "\r\n", ec);

        if (ec)
        {
            return;
        }

        response = receive_buffer(ec);

        if (!check_response(response, 334))
        {
            ec = rightway::smtp::error::access_denied;
            return;
        }

        if (ec)
        {
            return;
        }


        send_buffer(rightway::smtp::detail::base64::encode_string(pass) + "\r\n", ec);

        if (ec)
        {
            return;
        }

        response = receive_buffer(ec);

        if (ec)
        {
            return;
        }

        if (!check_response(response, 235))
        {
            ec = rightway::smtp::error::access_denied;
            return;
        }
    }

    void send(rightway::smtp::message & m, error_code & ec)
    {
        ec = success;

        if (!is_connected())
        {
            ec = rightway::smtp::error::not_connected;
            return;
        }

        send_buffer(std::string("MAIL FROM:") + m.from() + " \r\n", ec);

        if (ec)
        {
            return;
        }

        std::string response = receive_buffer(ec);

        if (ec)
        {
            return;
        }

        if (!check_response(response, 250))
        {
            ec = rightway::smtp::error::syntax_error;
            return;
        }

        send_buffer(std::string("RCPT TO:") + m.to() + " \r\n", ec);

        if (ec)
        {
            return;
        }

        response = receive_buffer(ec);

        if (ec)
        {
            return;
        }

        if (!check_response(response, 250))
        {
            ec = rightway::smtp::error::syntax_error;
            return;
        }

        send_buffer("DATA \r\n", ec);

        if (ec)
        {
            return;
        }

        response = receive_buffer(ec);

        if (ec)
        {
            return;
        }

        if (!check_response(response, 354))
        {
            ec = rightway::smtp::error::syntax_error;
            return;
        }

        send_buffer(m.formatted_message() + "\r\n.\r\n", ec);

        if (ec)
        {
            return;
        }

        response = receive_buffer(ec);

        if (ec)
        {
            return;
        }

        if (!check_response(response, 250))
        {
            ec = rightway::smtp::error::syntax_error;
            return;
        }
    }

private:
    std::string receive_buffer(error_code & ec)
    {
        ec = success;

        if (!is_connected())
        {
            ec = rightway::smtp::error::not_connected;
            return "";
        }

        fd_set   readfds;        
        FD_ZERO(&readfds);

        FD_SET(socket_, &readfds);

        timeval timeout = {0};
        timeout.tv_sec  = receive_timeout_;

        if (-1 == ::select(socket_ + 1, &readfds, 0, 0, &timeout))
        {
            ec = rightway::smtp::error::fd_set_failure;
            return "";
        }

        unsigned long bytes_available;
        if (::ioctlsocket(socket_, FIONREAD, &bytes_available) == SOCKET_ERROR)
        {
            bytes_available = 0;
        }

        std::vector<char> data(bytes_available + 1);
        int bytes = ::recv(socket_, &data[0], data.size(), 0);

        if (bytes <= 0)
        {
            rightway::system::error_code disconnect_error;
            disconnect(disconnect_error);

            ec = rightway::smtp::error::not_connected;
            return "";
        }
        
        data[bytes_available] = 0;
        return &data[0];
    }

    void send_buffer(const std::string & input, error_code & ec)
    {
        ec = success;

        if (!is_connected())
        {
            ec = rightway::smtp::error::not_connected;
            return;
        }

        fd_set   writefds;
        FD_ZERO(&writefds);

        FD_SET(socket_, &writefds);

        timeval timeout = {0};
        timeout.tv_sec  = send_timeout_;

        if (-1 == ::select(socket_ + 1, 0, &writefds, 0, &timeout))
        {
            ec = rightway::smtp::error::fd_set_failure;
            return;
        }

        if (SOCKET_ERROR == ::send(socket_, input.c_str(), input.length(), 0))
        {
            rightway::system::error_code disconnect_error;
            disconnect(disconnect_error);

            ec = rightway::smtp::error::not_connected;
            return;
        }
    }

private:
    bool check_response(const std::string & response, std::size_t code)
    {
        std::ostringstream oss;
        oss << code;

        return (0 == response.find(oss.str()));
    }

private:
    bool    initialized_;
    WSADATA wsa_data_;

    SOCKET  socket_;
};

template<>
template<>
pimpl<rightway::smtp::mailbox>::pointer_semantics::~pointer_semantics()
{
    // Always empty
}

}   // namespace system
}   // namespace rightway

#endif
