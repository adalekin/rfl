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

#include <rightway/smtp/message.hpp>
#include <rightway/smtp/detail/base64.hpp>

#include <fstream>
#include <sstream>

#include <vector>
#include <ctime>

namespace rightway { namespace smtp {

namespace {

inline std::string format_email(const std::string & address, const std::string & name)
{
    std::string email;

    if (name.empty())
    {
        email  = "<";
        email += address;
        email += ">";
    }
    else
    {
        email  = name;
        email  = " <";
        email += address;
        email += ">";
    }

    return email;    
}

}

std::string message::from(const std::string & address, const std::string & name)
{
    if (address.empty() && name.empty())
    {
        return from_address_;
    }

    std::string old_from = from_address_;

    from_address_ = address;
    from_name_    = name;

    return old_from;
}

std::string message::to  (const std::string & address, const std::string & name)
{
    if (address.empty() && name.empty())
    {
        return to_address_;
    }

    std::string old_to = to_address_;

    to_address_ = address;
    to_name_    = name;

    return old_to;
}

void message::body(const std::string & body)
{
    body_ = body;
}

void message::subject(const std::string & subject)
{
    subject_ = subject;
}

void message::attach(const std::string & path)
{
    attachments_.push_back(path);
}

std::string message::formatted_message()
{
    time_t rawtime;
    tm * timeinfo;
    char formatted_date[80];

    ::time(&rawtime);
    timeinfo = ::localtime(&rawtime);

    ::strftime(formatted_date, sizeof(formatted_date) / sizeof(formatted_date[0]), "%a, %d %b %Y %H:%M:%S", timeinfo);

    std::stringstream ss;

    ss << "From: "      << format_email(from_address_, from_name_) << "\r\n";
    ss << "To: "        << format_email(to_address_, to_name_)     << "\r\n";
    ss << "Subject: "   << subject_                                << "\r\n";
    ss << "Date: "      << formatted_date                          << "\r\n";
    ss << "X-Mailer: Rightway SMTP Library\r\n";

    if (attachments_.size())
    {
        ss << "MIME-Version: 1.0\r\n";
        ss << "Content-type: multipart/mixed; boundary=\"#BOUNDARY#\"\r\n";
    }
    else
    {
        ss << "MIME-Version: 1.0\r\n";
        ss << "Content-type: text/plain; charset=US-ASCII\r\n";
    }

    ss << "\r\n";

    if (attachments_.size())
    {
        ss << "\r\n--#BOUNDARY#\r\n";
        ss << "Content-Type: text/plain; charset=us-ascii\r\n";
        ss << "Content-Transfer-Encoding: quoted-printable\r\n\r\n";
    }

    ss << body_ << "\r\n";

    for (attachments::const_iterator it = attachments_.begin(); it != attachments_.end(); ++it)
    {
        std::string filename = it->c_str();
        std::string::size_type pos = filename.find_last_of('\\');

        if (pos != std::string::npos)
        {
            filename.erase(0, pos);
        }

        std::ifstream f(it->c_str(), std::ios::in | std::ios::binary);

        if (!f)
        {
            continue;
        }

        ss << "\r\n--#BOUNDARY#\r\n";
        ss << "Content-Type: application/octet-stream; name=" << filename << "\r\n";
        ss << "Content-Transfer-Encoding: base64\r\n";
        ss << "Content-Disposition: attachment; filename=" << filename << "\r\n\r\n";

        std::vector<char> buffer;
        std::ifstream::pos_type size = 0;

        if (f.seekg(0, std::ios::end))
        {
            size = f.tellg();
        }

        if (size && f.seekg(0, std::ios::beg))
        {
            buffer.resize(size);
            f.read(&buffer[0], size);
        }

        ss << rightway::smtp::detail::base64::encode(&buffer[0], buffer.size());
    }

    return ss.str();
}

}   // namespace smtp
}   // namespace rightway
