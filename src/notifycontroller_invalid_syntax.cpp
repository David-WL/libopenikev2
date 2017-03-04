/***************************************************************************
*   Copyright (C) 2005 by                                                 *
*   Pedro J. Fernandez Ruiz    pedroj@um.es                               *
*   Alejandro Perez Mendez     alex@um.es                                 *
*                                                                         *
*   This library is free software; you can redistribute it and/or         *
*   modify it under the terms of the GNU Lesser General Public            *
*   License as published by the Free Software Foundation; either          *
*   version 2.1 of the License, or (at your option) any later version.    *
*                                                                         *
*   This library is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
*   Lesser General Public License for more details.                       *
*                                                                         *
*   You should have received a copy of the GNU Lesser General Public      *
*   License along with this library; if not, write to the Free Software   *
*   Foundation, Inc., 51 Franklin St, Fifth Floor,                        *
*   Boston, MA  02110-1301  USA                                           *
***************************************************************************/
#include "notifycontroller_invalid_syntax.h"
#include "eventbus.h"
#include "buseventikesa.h"
#include "log.h"

namespace openikev2 {

    NotifyController_INVALID_SYNTAX::NotifyController_INVALID_SYNTAX() {}

    NotifyController_INVALID_SYNTAX::~NotifyController_INVALID_SYNTAX() {}

    IkeSa::NOTIFY_ACTION NotifyController_INVALID_SYNTAX::processNotify( Payload_NOTIFY& notify, Message& message, IkeSa& ike_sa, ChildSa* child_sa ) {
        assert( notify.notification_type == Payload_NOTIFY::INVALID_SYNTAX );

        // If is a request
        if ( message.message_type == Message::REQUEST ) {
            Log::writeLockedMessage( ike_sa.getLogId(), "INVALID_SYNTAX notify in a request.", Log::LOG_ERRO, true );
            ike_sa.sendNotifyResponse( message.exchange_type, Payload_NOTIFY::INVALID_SYNTAX);
            return IkeSa::NOTIFY_ACTION_ERROR;
        }

        // Check notify field correction
        if ( notify.protocol_id > Enums::PROTO_IKE || notify.spi_value.get() != NULL || notify.notification_data.get() != NULL ){
            Log::writeLockedMessage( ike_sa.getLogId(), "INVALID SYNTTAX in INVALID_SYNTAX notify", Log::LOG_ERRO, true );
            return IkeSa::NOTIFY_ACTION_ERROR;
        }

        Log::writeLockedMessage( ike_sa.getLogId(), "Peer reject request due to invalid syntax.", Log::LOG_ERRO, true );
        return IkeSa::NOTIFY_ACTION_ERROR;
    }
}
