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

#ifndef __RIGHTWAY_SYSTEM_ERROR_CODE_HPP__
#define __RIGHTWAY_SYSTEM_ERROR_CODE_HPP__

#include <string>

namespace rightway { namespace system {

enum generic_errors
{
    success = -1
};

class error_code;
class error_category;

class error_category
{
public:
    virtual ~error_category() {}
    virtual inline const char * name() const = 0;
    virtual inline std::string message(int value) const = 0;
};

class generic_category : public error_category
{
public:
    const char * name() const
    {
        return "system.basic";
    }

    std::string message(int value) const
    {
        switch (value)
        {
        case success:
            return "Success";
        }

        return "Basic error";
    }
};

inline generic_category & get_generic_category();
inline error_code make_error_code(generic_errors e);


class error_code
{
public:
    error_code()
        : val_(success)
        , cat_(&get_generic_category())
    {
    }

    error_code(int val, const error_category & cat)
        : val_(val)
        , cat_(&cat)
    {
    }

    template<class ErrorCode>
    error_code(ErrorCode e)
    {
        *this = make_error_code(e);
    }

public:
    std::string message() const
    {
        return cat_->message(value());
    }

    int value() const
    {
        return val_;
    }

    const error_category & category() const
    {
        return *cat_;
    }


public:
    operator bool() const
    {
        return !operator !();
    }

    bool operator !() const
    {
        return value() == success;
    }

private:
    int val_;
    const error_category* cat_;
};

inline generic_category & get_generic_category()
{
    static generic_category instance;
    return instance;
}

inline error_code make_error_code(generic_errors e)
{
    return error_code(static_cast<int>(e), get_generic_category());
}

}   // namespace system
}   // namespace rightway

#endif
