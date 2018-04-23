//
// Created by hqnders on 20/04/18.
//

#ifndef PRODUCTION_LINE_CONTROL_NETWORKCOMPONENT_H
#define PRODUCTION_LINE_CONTROL_NETWORKCOMPONENT_H

#include "network/Connection.h"

namespace Communication {
    class NetworkComponent : public Network::IConnectionHandler {
    public:
        NetworkComponent();
        virtual ~NetworkComponent();

        virtual void onConnectionEstablished(Network::ConnectionPtr connection);
        virtual void onConnectionDisconnected(Network::ConnectionPtr connection, const boost::system::error_code &error);
        virtual void onConnectionMessageReceived(Network::ConnectionPtr connection, Network::Message &message);
    };
}


#endif //PRODUCTION_LINE_CONTROL_NETWORKCOMPONENT_H
