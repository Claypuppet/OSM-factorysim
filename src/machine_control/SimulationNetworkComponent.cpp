
// standard libraries
#include <iostream>
#include <cereal/archives/portable_binary.hpp>
#include <cereal/types/vector.hpp>

// libraries
#include <network/Protocol.h>

// other
#include "SimulationNetworkComponent.h"
#include "ControllerNotificationEventIds.h"


namespace SimulationCommunication {


	void SimulationNetworkComponent::onConnectionFailed(Network::ConnectionPtr connection, const boost::system::error_code &error) {
		IConnectionHandler::onConnectionFailed(connection, error);
		std::cout << "not connected" << std::endl;
	}

	void SimulationNetworkComponent::onConnectionEstablished(Network::ConnectionPtr connection) {
		mConnection = connection;
	}

	void SimulationNetworkComponent::onConnectionDisconnected(Network::ConnectionPtr connection, const boost::system::error_code &error) {
		std::cout << "dc" << std::endl;
		std::cout << "not connected 2" << std::endl;

	}

	void SimulationNetworkComponent::onConnectionMessageReceived(Network::ConnectionPtr connection, Network::Message &message) {
		std::cout << message.mBody << std::endl;
		switch(message.getMessageType()){
			case Network::Protocol::kSimMessageTypeConfig : {
                Models::MachinePtr machinePtr;

                if (deserializeSimulationMachineInfo(message.mBody, machinePtr)) {
                    onSimulationMachineInfoReceived(machinePtr);
                }

                break;
            } case Network::Protocol::kSimMessageTypeTurnOn : {
                onTurnOnReceived();
                break;
            } case Network::Protocol::kSimMessageTypeTurnOff : {
                onTurnOffReceived();
                break;
            } default : {
                break;
            }
		}
	}

	bool SimulationNetworkComponent::deserializeSimulationMachineInfo(const std::string &string, Models::MachinePtr machinePtr) {
		std::stringstream binaryStream((std::ios::in | std::ios::binary));
		binaryStream.str(string);
		cereal::PortableBinaryInputArchive archive(binaryStream);
		archive(*machinePtr);
		return true; // TODO : implement boolean
	}

	void SimulationNetworkComponent::onSimulationMachineInfoReceived(Models::MachinePtr machinePtr) {
		auto event = makeNotifcation(Patterns::NotifyObserver::NotifyTrigger(), ControllerEvents::kNotifyEventTypeMachineInfoReceived);
		event.addArgument(machinePtr);
		notifyObservers(event);
	}

	void SimulationNetworkComponent::onTurnOffReceived() {
        auto notification = makeNotifcation(Patterns::NotifyObserver::NotifyTrigger(), ControllerEvents::kNotifyEventTypeTurnOffReceived);
        notifyObservers(notification);
	}

	void SimulationNetworkComponent::onTurnOnReceived() {
        auto notification = makeNotifcation(Patterns::NotifyObserver::NotifyTrigger(), ControllerEvents::kNotifyEventTypeTurnOnReceived);
        notifyObservers(notification);
	}
}
