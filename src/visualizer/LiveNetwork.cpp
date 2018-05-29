//
// Created by don on 28-5-18.
//

#include "LiveNetwork.h"

namespace live{


void LiveNetwork::onConnectionEstablished(network::ConnectionPtr connection) {

}
void LiveNetwork::onConnectionDisconnected(network::ConnectionPtr connection,
                                                 const boost::system::error_code &error) {

}
void LiveNetwork::onConnectionMessageReceived(network::ConnectionPtr connection, network::Message &message) {

}

}
