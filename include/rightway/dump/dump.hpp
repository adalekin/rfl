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

#ifndef __RIGHTWAY_DUMP_DUMP_HPP__
#define __RIGHTWAY_DUMP_DUMP_HPP__

#include <rightway/dump/error.hpp>
#include <string>

namespace rightway { namespace dump {

/*!
 *  \brief Generate the crash report and save it into the specified file.
 *
 *  \param[in]  filename The file path to save the crash report to.
 *  \param[out] ec       Set to indicate what error occurred, if any. 
 */
void save(const std::string & filename, rightway::system::error_code & ec);

}   // namespace dump
}   // namespace rightway

#endif
