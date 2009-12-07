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

#include <rightway/smtp/mailbox.hpp>
#include <rightway/smtp/detail/win_mailbox.hpp>

namespace rightway { namespace smtp {

mailbox::mailbox()
    : rightway::system::pimpl<mailbox>::pointer_semantics(new rightway::system::pimpl<mailbox>::implementation())
{
}

mailbox::~mailbox()
{
}

void mailbox::connect(const std::string & server, std::size_t port, rightway::system::error_code & ec)
{
    implementation & self = **this;
    self.connect(server, port, ec);
}

void mailbox::auth(const std::string & username, const std::string & pass, rightway::system::error_code & ec)
{
    implementation & self = **this;
    self.auth(username, pass, ec);
}

void mailbox::send(message & m, rightway::system::error_code & ec)
{
    implementation & self = **this;
    self.send(m, ec);
}

}   // namespace smtp
}   // namespace rightway
