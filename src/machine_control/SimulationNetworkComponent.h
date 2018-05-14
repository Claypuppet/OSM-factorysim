#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONSimulationNetworkComponent_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONSimulationNetworkComponent_H

// standard library includes
// -

// libary includes
#include <patterns/notifyobserver/Notifier.hpp>
#include <network/Connection.h>
#include <models/Machine.h>

// other includes
// -

namespace SimulationCommunication {

	class SimulationNetworkComponent;
	typedef std::shared_ptr<SimulationNetworkComponent> SimulationNetworkComponentPtr;

    class SimulationNetworkComponent :
			public Network::IConnectionHandler,
			public patterns::NotifyObserver::Notifier
	{
    public:
        SimulationNetworkComponent() = default;
        virtual ~SimulationNetworkComponent() = default;

    private:
        void onConnectionFailed(Network::ConnectionPtr connection, const boost::system::error_code &error) override;
        void onConnectionEstablished(Network::ConnectionPtr connection) override;
        void onConnectionDisconnected(Network::ConnectionPtr connection, const boost::system::error_code &error) override;
        void onConnectionMessageReceived(Network::ConnectionPtr connection, Network::Message &message) override;

        Network::ConnectionPtr mConnection;

        /**
         * Deserialize the string (body), apply to machine. Returns true if successfully deserialized
         * @param body : body string from message
         * @param machine : machine model to fill
         * @return bool : success
         */
        bool deserializeSimulationMachineInfo(const std::string &body, models::MachinePtr machinePtr);

        /**
         * Handles new machine info receive
         * @param machine
         */
        void onSimulationMachineInfoReceived(models::MachinePtr machinePtr);

        /**
         * Handles machine turn on command
         */
        void onTurnOnReceived();

		/**
		 * Handles machine turn off command
		 */
        void onTurnOffReceived();
    };
}



#endif //PRODUCTION_LINE_CONTROL_SIMULATIONSimulationNetworkComponent_H
