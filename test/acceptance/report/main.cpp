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

#include <rightway/report/report.hpp>

#include <iostream>

int main(int argc, char * argv[])
{
    rightway::report::service::email service("your@email.com", "This is a bug");

    service.description("bla bla bla");
    service.file("rfl_acceptance_report.exe");

    rightway::system::error_code error;

    service.report(error);

    if (error)
    {
        std::cerr << error.message() << std::endl;
        return -1;
    }

    return 0;
}
