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

#ifndef RIGHTWAY_SMTP_DETAIL_BASE64_HPP__
#define RIGHTWAY_SMTP_DETAIL_BASE64_HPP__

namespace rightway { namespace smtp { namespace detail { namespace base64 {

inline std::string encode(const char * p, std::size_t size)
{
    const static char cb64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    std::string result;

    for (std::size_t i = 0, end = size; i < end; i += 3)
    {
        long l = (                   ((long) p[i    ]) << 16       ) |
                 (((i + 1) < end) ? (((long) p[i + 1]) << 8  ) : 0 ) |
                 (((i + 2) < end) ? ( (long) p[i + 2]        ) : 0 );
        
        result += cb64[(l >> 18) & 0x3F];
        result += cb64[(l >> 12) & 0x3F];
        if (i + 1 < end) result += cb64[(l>> 6) & 0x3F];
        if (i + 2 < end) result += cb64[(l    ) & 0x3F];
    }
    
    switch (size % 3)
    {
    case 1:
        result += '=';
    case 2:
        result += '=';
    }

    return result;
}

inline std::string encode_string(const std::string & input)
{
    return encode(input.c_str(), input.length());
}

}   // namespace base64
}   // namespace detail
}   // namespace smtp
}   // namespace rightway

#endif
