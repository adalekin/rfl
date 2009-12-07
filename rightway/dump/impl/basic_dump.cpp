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

#include <rightway/dump/detail/basic_dump.hpp>

#if defined(OS_WINDOWS)
#include <rightway/dump/detail/win_basic_dump_impl.hpp>
#else
#error Your platform isn't supported yet.
#endif  // OS_WINDOWS

namespace rightway { namespace dump { namespace detail {

basic_dump::basic_dump()
    : rightway::system::pimpl<basic_dump>::pointer_semantics(new rightway::system::pimpl<basic_dump>::implementation())
{
}

basic_dump::~basic_dump()
{
}

void basic_dump::save(const std::string & filename, rightway::system::error_code & ec)
{
    implementation & self = **this;
    self.save(filename, ec);
}

}   // namespace detail
}   // namespace dump
}   // namespace rightway
