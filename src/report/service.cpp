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

#include <rightway/report/service.hpp>
#include "dns.hpp"

#include <rightway/smtp/smtp.hpp>

#include <iostream>

namespace rightway { namespace report { namespace service {

void base_holder::description(const std::string & description)
{
    description_ = description;
}

void base_holder::file(const std::string & path)
{
    files_.push_back(path);
}





email::email(const std::string & address, const std::string & subject)
    : address_(address)
    , subject_(subject)
{
}

void email::report(rightway::system::error_code & ec)
{
    std::string server = detail::dns_mail_exchanger(address_, ec);

    if (ec)
    {
        return;
    }
	
	rightway::smtp::mailbox mb;	
	mb.connect(server, 25, ec);

    if (ec)
    {
        return;
    }
	
    rightway::smtp::message m;

    m.from(address_);
    m.to  (address_);

    m.subject(subject_);
    m.body(description_);

    for (files::const_iterator it = files_.begin(), end = files_.end(); it != end; ++it)
    {
        m.attach(it->c_str());
    }

    mb.send(m, ec);

    if (ec)
    {
        return;
    }
}


}   // namespace service
}   // namespace report
}   // namespace rightway
