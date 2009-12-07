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

#ifndef __RIGHTWAY_SMTP_MESSAGE_HPP__
#define __RIGHTWAY_SMTP_MESSAGE_HPP__

#include <rightway/system/noncopyable.hpp>

#include <list>
#include <string>

namespace rightway { namespace smtp {

/*!
 *  \class rightway::smtp::message message.hpp <rightway/smtp/message.hpp>
 *
 *  \brief The SMTP message type.
 *  \sa mailbox
 */
class message : rightway::system::noncopyable
{
    typedef std::list<std::string> attachments;

public:
    /*!
     *  \brief Gets or sets the from address for this e-mail message.
     *
     *  \param[in]  address The from e-mail address.
     *  \param[in]  name    The from real name.
     *
     *  \return If address is not empty this function returns the old from e-mail address
     *          and the from e-mail address otherwise.
     */
    std::string from(const std::string & address = "", const std::string & name = "");

    /*!
     *  \brief Gets or sets the to address for this e-mail message.
     *
     *  \param[in]  address The to e-mail address.
     *  \param[in]  name    The to real name.
     *
     *  \return If address is not empty this function returns the old to e-mail address
     *          and the to e-mail address otherwise.
     */
    std::string to  (const std::string & address = "", const std::string & name = "");

    /*!
     *  \brief Gets or sets the message body.
     *
     *  \param[in]  body The message body.
     */
    void body(const std::string & body);

    /*!
     *  \brief Gets or sets the message subject.
     *
     *  \param[in]  subject The message subject.
     */
    void subject(const std::string & subject);

    /*!
     *  \brief Adds the new attachment to this e-mail message.
     *
     *  \param[in]  path The attachment path.
     */
    void attach(const std::string & path);

public:
    std::string formatted_message();

private:
    std::string from_address_;
    std::string from_name_;

    std::string to_address_;
    std::string to_name_;

    std::string subject_;
    std::string body_;

    attachments attachments_;
};

}   // namespace smtp
}   // namespace rightway

#endif
