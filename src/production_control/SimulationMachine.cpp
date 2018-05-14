//
// Created by don on 20-4-18.
//

#include <cereal/archives/portable_binary.hpp>
#include <network/Protocol.h>
#include "SimulationMachine.h"

namespace simulation {

	SimulationMachine::SimulationMachine(const models::Machine &aMachine) :
			core::Machine(aMachine), simConnection(nullptr), ready(false)
	{
	}

	SimulationMachine::SimulationMachine(const SimulationMachine &aMachine) :
			core::Machine(aMachine), simConnection(nullptr), ready(false)
	{
	}

	SimulationMachine& SimulationMachine::operator=(const SimulationMachine& rhs) {
		if(this != &rhs)
		{
			core::Machine::operator=(rhs);
			simConnection = rhs.simConnection;
		}
		return *this;
	}

	bool SimulationMachine::isSimulationConnected() const{
		return !!simConnection;
	}

	void SimulationMachine::sendSimulationMessage(Network::Message &msg) {
		if (isSimulationConnected()){
			simConnection->writeMessage(msg);
		}
	}

	void SimulationMachine::setSimulationConnection(Network::ConnectionPtr &aConnection) {
		simConnection = aConnection;
	}

	void SimulationMachine::sendSimulationConfiguration() {
		Network::Message message(Network::Protocol::SimMessageType::kSimMessageTypeConfig);
		auto machineInfo = static_cast<models::Machine>(*this);
		message.setBody<models::Machine>(machineInfo);
		sendSimulationMessage(message);
	}

	void SimulationMachine::sendTurnOnCommand() {
//	  Network::Message message(Network::Protocol::SimMessageType::);

	}

	bool SimulationMachine::isReadyForSimulation() const {
	  return isSimulationConnected() && ready;
	}

	void SimulationMachine::setReady(bool aReady) {
	  SimulationMachine::ready = true;
	}

}

