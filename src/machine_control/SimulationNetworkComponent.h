//
// Created by hqnders on 20/04/18.
//

#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONSimulationNetworkComponent_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONSimulationNetworkComponent_H

#include <patterns/notifyobserver/Notifier.hpp>
#include "network/Connection.h"

namespace SimulationCommunication {

	class SimulationNetworkComponent;

	typedef std::shared_ptr<SimulationNetworkComponent> SimulationNetworkComponentPtr;

    class SimulationNetworkComponent :
			public Network::IConnectionHandler,
			public Patterns::NotifyObserver::Notifier
	{
    public:
        SimulationNetworkComponent() = default;
        ~SimulationNetworkComponent() = default;

        Network::ConnectionPtr getConnection();

    private:
        void onConnectionFailed(Network::ConnectionPtr connection, const boost::system::error_code &error) override;
        void onConnectionEstablished(Network::ConnectionPtr connection) override;
        void onConnectionDisconnected(Network::ConnectionPtr connection, const boost::system::error_code &error) override;
        void onConnectionMessageReceived(Network::ConnectionPtr connection, Network::Message &message) override;

        Network::ConnectionPtr mConnection;

        void handleReconfigureMessage();
        void handleProcessProductMessage();

        void onConfigurationReceived(std::string);
    };
}



#endif //PRODUCTION_LINE_CONTROL_SIMULATIONSimulationNetworkComponent_H
