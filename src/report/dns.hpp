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

#ifndef RIGHTWAY_REPORT_DETIAL_DNS_HPP__
#define RIGHTWAY_REPORT_DETIAL_DNS_HPP__

#include <rightway/report/error.hpp>
#include <string>

namespace rightway { namespace report { namespace detail {

std::string dns_mail_exchanger(const std::string & address, rightway::system::error_code & ec);

}   // namespace detail
}   // namespace report
}   // namespace rightway

#endif
