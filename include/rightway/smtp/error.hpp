/*
 * Rightway Feedback Libraries.
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

#ifndef __RIGHTWAY_SMTP_ERROR_HPP__
#define __RIGHTWAY_SMTP_ERROR_HPP__

#include <rightway/system/error_code.hpp>
#include <string>

namespace rightway { namespace smtp { namespace error {

enum basic_errors
{
    not_supported,
    access_denied,
    syntax_error
};

enum network_errors
{
    wsa_startup,
    wsa_version,
    not_resolved,
    invalid_socket,
    not_connected,
    fd_set_failure
};

enum date_errors
{
    invalid_argument
};

}   // namespace error

namespace detail {

class basic_category : public rightway::system::error_category
{
public:
    virtual inline const char * name() const
    {
        return "smtp.basic";
    }

    virtual inline std::string message(int value) const
    {
        switch (value)
        {
        case error::not_supported:
            return "SMTP server doesn't supported yet";
        case error::access_denied:
            return "Access denied";
        case error::syntax_error:
            return "Syntax error";
        }

        return "Basic error";
    }
};

class network_category : public rightway::system::error_category
{
public:
    virtual inline const char * name() const
    {
        return "smtp.network";
    }

    virtual inline std::string message(int value) const
    {
        switch (value)
        {
        case error::wsa_startup:
            return "Failed to initialize WSA";
        case error::wsa_version:
            return "Wrong WSA version";
        case error::not_resolved:
            return "Couldn't resolve hostname";
        case error::invalid_socket:
            return "Invalid socket";
        case error::not_connected:
            return "Connection isn't established";
        case error::fd_set_failure:
            return "Failed to select fd_set structure";
        }

        return "Network error";
    }
};

class date_category : public rightway::system::error_category
{
public:
    virtual inline const char * name() const
    {
        return "smtp.date";
    }

    virtual inline std::string message(int value) const
    {
        switch (value)
        {
        case error::invalid_argument:
            return "Failed to initialize WSA";
        }

        return "Date error";
    }
};

inline basic_category & get_basic_category()
{
    static basic_category instance;
    return instance;
}

inline network_category & get_network_category()
{
    static network_category instance;
    return instance;
}

inline date_category & get_date_category()
{
    static date_category instance;
    return instance;
}

}   // namespace detail
}   // namespace smtp

namespace system {

inline rightway::system::error_code make_error_code(rightway::smtp::error::basic_errors e)
{
    return rightway::system::error_code(
        static_cast<int>(e), rightway::smtp::detail::get_basic_category());
}

inline rightway::system::error_code make_error_code(rightway::smtp::error::network_errors e)
{
    return rightway::system::error_code(
        static_cast<int>(e), rightway::smtp::detail::get_network_category());
}

inline rightway::system::error_code make_error_code(rightway::smtp::error::date_errors e)
{
    return rightway::system::error_code(
        static_cast<int>(e), rightway::smtp::detail::get_date_category());
}

}   // namespace system
}   // namespace rightway


#endif
