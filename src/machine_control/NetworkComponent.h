//
// Created by klei on 4/19/18.
//

#ifndef PRODUCTION_LINE_CONTROL_NETWORKCOMPONENT_H
#define PRODUCTION_LINE_CONTROL_NETWORKCOMPONENT_H

#include "network/Connection.h"


class NetworkComponent : public network::IConnectionHandler {
public:
	NetworkComponent() = default;
	~NetworkComponent() = default;


private:
	void onConnectionFailed(network::ConnectionPtr connection, const boost::system::error_code &error) override;

	void onConnectionEstablished(network::ConnectionPtr connection) override;

	void onConnectionDisconnected(network::ConnectionPtr connection, const boost::system::error_code &error) override;

	void onConnectionMessageReceived(network::ConnectionPtr connection, network::Message &message) override;

	void onConnectionMessageSent(network::ConnectionPtr connection, network::Message &message) override;


};


#endif //PRODUCTION_LINE_CONTROL_NETWORKCOMPONENT_H
