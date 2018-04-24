//
// Created by don on 23-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_TESTCONNECTIONHANDLER_H
#define PRODUCTION_LINE_CONTROL_TESTCONNECTIONHANDLER_H

#include <network/Connection.h>

class TestConnectionHandler : public Network::IConnectionHandler{
public:
    TestConnectionHandler() = default;
    ~TestConnectionHandler() = default;

    void onConnectionFailed(Network::ConnectionPtr connection, const boost::system::error_code &error) override;

    void onConnectionEstablished(Network::ConnectionPtr connection) override;

    void onConnectionDisconnected(Network::ConnectionPtr connection, const boost::system::error_code &error) override;

    void onConnectionMessageReceived(Network::ConnectionPtr connection, Network::Message &message) override;

    void onConnectionMessageSent(Network::ConnectionPtr connection, Network::Message &message) override;
};


#endif //PRODUCTION_LINE_CONTROL_TESTCONNECTIONHANDLER_H
