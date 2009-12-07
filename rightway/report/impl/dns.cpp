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

#include <rightway/report/detail/dns.hpp>

#include <Windows.h>
#include <Windns.h>

#pragma comment(lib, "Dnsapi.lib")

#include <iostream>

namespace rightway { namespace report { namespace detail {

std::string dns_mail_exchanger(const std::string & address, rightway::system::error_code & ec)
{
    std::string domain = address;
    std::string::size_type pos = domain.find_last_of('@');

    if (std::string::npos == pos)
    {
        ec = rightway::report::error::wrong_address;
        return "";
    }

    domain.erase(0, pos + 1);

    DNS_RECORD* ppQueryResultsSet = NULL;

    DNS_STATUS status = ::DnsQuery_A( domain.c_str(), DNS_TYPE_MX, 
        DNS_QUERY_STANDARD, NULL, 
        &ppQueryResultsSet, NULL );

    if (status)
    {
        ec = rightway::report::error::resolve_failed;
        return "";
    }

    return ppQueryResultsSet->Data.MX.pNameExchange;
}

}   // namespace detail
}   // namespace report
}   // namespace rightway