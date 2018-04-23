//
// Created by don on 19-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_COMMNET_H
#define PRODUCTION_LINE_CONTROL_COMMNET_H

#include "network/Connection.h"
#include "Application.h"


class AppConnectionHandler : public Network::IConnectionHandler {
public:
    AppConnectionHandler(Application *app);
    ~AppConnectionHandler() = default;

    //Move to private when network component works
    void handleRegisterMachine(const std::string& msgBody, Network::ConnectionPtr connection);
private:
    void onConnectionFailed(Network::ConnectionPtr connection, const boost::system::error_code &error) override;

    void onConnectionEstablished(Network::ConnectionPtr connection) override;

    void
    onConnectionDisconnected(Network::ConnectionPtr connection, const boost::system::error_code &error) override;

    void onConnectionMessageReceived(Network::ConnectionPtr connection, Network::Message &message) override;

    void onConnectionMessageSent(Network::ConnectionPtr connection, Network::Message &message) override;
    Application* app;
};


#endif //PRODUCTION_LINE_CONTROL_COMMNET_H
