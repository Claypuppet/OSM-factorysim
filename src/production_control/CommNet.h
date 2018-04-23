//
// Created by don on 19-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_COMMNET_H
#define PRODUCTION_LINE_CONTROL_COMMNET_H

#include "network/Connection.h"
#include "Application.h"


class CommNet : public network::IConnectionHandler {
public:
    CommNet(Application *app);
    ~CommNet() = default;
private:
    void onConnectionFailed(network::ConnectionPtr connection, const boost::system::error_code &error) override;

    void onConnectionEstablished(network::ConnectionPtr connection) override;

    void
    onConnectionDisconnected(network::ConnectionPtr connection, const boost::system::error_code &error) override;

    void onConnectionMessageReceived(network::ConnectionPtr connection, network::Message &message) override;

    void onConnectionMessageSent(network::ConnectionPtr connection, network::Message &message) override;
    Application* app;
};


#endif //PRODUCTION_LINE_CONTROL_COMMNET_H
