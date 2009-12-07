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

#ifndef __RIGHTWAY_REPORT_ERROR_HPP__
#define __RIGHTWAY_REPORT_ERROR_HPP__

#include <rightway/system/error_code.hpp>
#include <string>

namespace rightway { namespace report { namespace error {

enum basic_errors
{
    wrong_address,
    resolve_failed
};

}   // namespace error

namespace detail {

class basic_category : public rightway::system::error_category
{
public:
    virtual inline const char * name() const
    {
        return "report.basic";
    }

    virtual inline std::string message(int value) const
    {
        switch (value)
        {
        case error::wrong_address:
            return "Wrong address format";
        case error::resolve_failed:
            return "Failed to resolve domain name";
        }

        return "Basic error";
    }
};

inline basic_category & get_basic_category()
{
    static basic_category instance;
    return instance;
}

}   // namespace detail
}   // namespace report

namespace system {

inline rightway::system::error_code make_error_code(rightway::report::error::basic_errors e)
{
    return rightway::system::error_code(
        static_cast<int>(e), rightway::report::detail::get_basic_category());
}

}   // namespace system
}   // namespace rightway

#endif
