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

#ifndef __RIGHTWAY_REPORT_CHANNEL_HPP__
#define __RIGHTWAY_REPORT_CHANNEL_HPP__

#include <rightway/report/error.hpp>
#include <rightway/smtp/smtp.hpp>
#include <list>

namespace rightway { namespace report { namespace service {

class base
{
public:
    virtual void description(const std::string & description)   = 0;
    virtual void file   (const std::string & path)              = 0;

public:
    virtual void report(rightway::system::error_code & ec)  = 0;
};

class base_holder : public base
{
protected:
    typedef std::list<std::string> files;

public:
    virtual void description(const std::string & description);
    virtual void file(const std::string & path);

protected:
    std::string description_;
    files       files_;
};

/*!
 * \class rightway::report::service service.hpp <rightway/report/service.hpp>
 *
 * \brief The e-mail report service class.
 *
 * This class provides functionality to send report via e-mail. 
 *
 * \b Examples
 *
 * \b Send \b report \b via \b e-mail
 *
 * You must open a connection to an SMTP server before sending messages.
 * The first argument is the address of your SMTP server, and the second argument is the port number.
 * Using rightway::smtp::mailbox::connect is the simplest way to do this.
 * This way, the SMTP connection is closed automatically after the mailbox object will be destroyed. 
 *
 * \code
 * rightway::report::service::email service("your@email.com", "This is a bug");
 *
 * service.description("Put your detailed description here");
 * service.file("screen.jpg");
 * 
 * rightway::system::error_code error;
 *
 * service.report(error);
 * 
 * if (error)
 * {
 *     // ... handle error here
 * }
 * \endcode
 *
 */
class email : public base_holder
{
public:
    /*!
     * \brief Construct an email.
	 *
     *  \param[in]  address The destination e-mail address.
     *  \param[in]  subject The subject of the message.
     */
    email(const std::string & address, const std::string & subject);

public:
    /*!
     *  \brief Send report via e-mail.
     *
     *  \param[out] ec     Set to indicate what error occurred, if any. 
     */
    virtual void report(rightway::system::error_code & ec);

private:
    std::string address_;
    std::string subject_;
};

}   // namespace service
}   // namespace report
}   // namespace rightway

#endif
