//
// Created by klei on 4/19/18.
//

#ifndef PRODUCTION_LINE_CONTROL_NetworkCOMPONENT_H
#define PRODUCTION_LINE_CONTROL_NetworkCOMPONENT_H

#include <patterns/notifyobserver/Notifier.hpp>
#include "network/Connection.h"

namespace Communication {
	class NetworkComponent : public Network::IConnectionHandler, public patterns::NotifyObserver::Notifier {
	public:
		NetworkComponent();
		~NetworkComponent() = default;

		const void sendHello();

		/**
		 * A function that sends a message to production control to register this machine
		 * @param machineId : The id of the machine
		 */
		void sendRegisterMessage(const uint16_t machineId);

		Network::ConnectionPtr getConnection();

	private:
		void onConnectionFailed(Network::ConnectionPtr connection, const boost::system::error_code &error) override;
		void onConnectionEstablished(Network::ConnectionPtr connection) override;
		void onConnectionDisconnected(Network::ConnectionPtr connection, const boost::system::error_code &error) override;
		void onConnectionMessageReceived(Network::ConnectionPtr connection, Network::Message &message) override;

		Network::ConnectionPtr mConnection;

		void handleReconfigureMessage();
		void handleProcessProductMessage();

	};
}


#endif //PRODUCTION_LINE_CONTROL_NetworkCOMPONENT_H
