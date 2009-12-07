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

#ifndef __RIGHTWAY_SMTP_MAILBOX_HPP__
#define __RIGHTWAY_SMTP_MAILBOX_HPP__

#include <rightway/smtp/error.hpp>
#include <rightway/smtp/message.hpp>

#include <rightway/system/pimpl.hpp>

namespace rightway { namespace smtp {

/*!
 * \class rightway::smtp::mailbox mailbox.hpp <rightway/smtp/mailbox.hpp>
 *
 * \brief The SMTP mailbox type.
 *
 * This class provides functionality to send internet mail via SMTP, the Simple Mail Transfer Protocol.
 * For details of SMTP itself, see [RFC2821] (www.ietf.org/rfc/rfc2821.txt). 
 *
 * \b Examples
 *
 * \b Connecting \b to \b the \b SMTP \b Server
 *
 * You must open a connection to an SMTP server before sending messages.
 * The first argument is the address of your SMTP server, and the second argument is the port number.
 * Using rightway::smtp::mailbox::connect is the simplest way to do this.
 * This way, the SMTP connection is closed automatically after the mailbox object will be destroyed. 
 *
 * \code
 * #include <rightway/smtp/smtp.hpp>
 * 
 * ...
 *
 * rightway::system::error_code error;
 * rightway::smtp::mailbox mail;
 * 
 * // Connect to the SMTP server
 * mail.connect("your.smtp.server", 25, error);
 *
 * if (error)
 * {
 *     // Handle error here
 * }
 * \endcode
 *
 * \b SMTP \b Authentification
 *
 * \code
 * ...
 *
 * mail.auth("username", "password", error);
 *
 * if (error)
 * {
 *     // Handle error here
 * }
 * \endcode
 *
 * \b Composing \b And \b Sending \b Messages
 *
 * \code
 * ...
 *
 * // Compose the message
 * rightway::smtp::message m;
 *
 * m.from("your@email.com", "Your Name");
 * m.to("to@email.com");
 *
 * m.body("hello world");
 * 
 * // Send the message through the SMTP server
 * mail.send(m, error);
 * 
 * if (error)
 * {
 *     // Handle error here
 * }
 *
 * \endcode
 */
class mailbox : public rightway::system::pimpl<mailbox>::pointer_semantics
{
public:
    /*!
     * \brief Construct a mailbox.
     */
    mailbox();

    /*!
     * \brief Destruct a mailbox.
     */
    ~mailbox();

public:
    /*!
     *  \brief Connect the mailbox to the specified server.
     *
     *  \param[in]  server The SMTP server hostname or IP address.
     *  \param[in]  port   The SMTP server port.
     *  \param[out] ec     Set to indicate what error occurred, if any. 
     */
    void connect(const std::string & server, std::size_t port, rightway::system::error_code & ec);

    /*!
     *  \brief Authorize the mailbox on the specified server.
     *
     *  \param[in]  username The SMTP server username.
     *  \param[in]  pass     The SMTP server password.
     *  \param[out] ec     Set to indicate what error occurred, if any. 
     */
    void auth(const std::string & username, const std::string & pass, rightway::system::error_code & ec);

    /*!
     *  \brief Send the message through the SMTP server.
     *
     *  \param[in]  m  The e-mail message object.
     *  \param[out] ec Set to indicate what error occurred, if any. 
     */
    void send(message & m, rightway::system::error_code & ec);
};

}   // namespace smtp
}   // namespace rightway

#endif
