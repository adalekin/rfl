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

#ifndef RIGHTWAY_SYSTEM_COMPILE_TIME_HPP__
#define RIGHTWAY_SYSTEM_COMPILE_TIME_HPP__

namespace rightway { namespace system { namespace compile_time {

template<class T, class U>
class conversion
{
    typedef char  small;
    class         big { char dummy[2]; };

    static small test(U);
    static big   test(...);

    static T make_type();

public:
    enum { same_type = 0 };
    enum { exists = sizeof(test(make_type())) == sizeof(small) };
};

template<class T>
class conversion<T, T>
{
public:
    enum { same_type = 1 };
};

template<bool> struct assert;
template<>     struct assert<true> {};

}   // namespace compile_time
}   // namespace system
}   // namespace rightway

#endif

