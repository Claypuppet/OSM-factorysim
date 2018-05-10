//
// Created by sven on 25-4-18.
//

#include <network/Protocol.h>
#include <cereal/archives/portable_binary.hpp>
#include "SimulationConnectionHandler.h"
#include "NotificationTypes.h"

namespace simulation {
	void SimulationConnectionHandler::onConnectionFailed(Network::ConnectionPtr connection,
														 const boost::system::error_code &error) {
		IConnectionHandler::onConnectionFailed(connection, error);
		std::cout << "not connected" << std::endl;
	}

	void SimulationConnectionHandler::onConnectionEstablished(Network::ConnectionPtr connection) {
		// No implementation needed, machine should register for connection to be used.
	}

	void SimulationConnectionHandler::onConnectionDisconnected(Network::ConnectionPtr connection,
															   const boost::system::error_code &error) {
		std::cout << "dc" << std::endl;
		std::cout << "not connected 2" << std::endl;

	}


	void SimulationConnectionHandler::onConnectionMessageReceived(Network::ConnectionPtr connection,
																  Network::Message &message) {
		std::cout << message.mBody << std::endl;
		switch (message.getMessageType()) {
			case Network::Protocol::kSimMessageTypeRegister:
				//TODO set right event id
				auto notification = makeNotifcation(Patterns::NotifyObserver::NotifyTrigger(),
													NotifyEventIds::eControllerRegisterMachine);

				uint16_t machineId = std::strtoul(message.getBody().c_str(), nullptr, 10);
				notification.setArgument(0, machineId);
				notification.setArgument(1, connection);

				notifyObservers(notification);
				break;
		}
	}

	bool SimulationConnectionHandler::deserializeSimulationMachineInfo(const std::string &string,
																	   Models::MachinePtr machine) {
//		std::stringstream binaryStream((std::ios::in | std::ios::binary));
//		binaryStream.str(string);
//		cereal::PortableBinaryInputArchive archive(binaryStream);
//		archive(machine);
		return !!machine;
	}

	void SimulationConnectionHandler::onSimulationMachineInfoReceived(const Models::Machine &machine) {
//		auto machinePtr = std::make_shared<Model::Machine>(machine);


	}

	void handleRegisterMachineMessage(const std::string &messageBody) {

	}


}