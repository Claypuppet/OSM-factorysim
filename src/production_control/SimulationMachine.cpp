//
// Created by don on 20-4-18.
//

#include <cereal/archives/portable_binary.hpp>
#include <network/Protocol.h>
#include "SimulationMachine.h"

namespace Simulation {

	SimulationMachine::SimulationMachine(const models::Machine &aMachine) :
			Core::Machine(aMachine), simConnection(nullptr)
	{
	}

	SimulationMachine::SimulationMachine(const SimulationMachine &aMachine) :
			Core::Machine(aMachine), simConnection(nullptr)
	{
	}

	SimulationMachine& SimulationMachine::operator=(const SimulationMachine& rhs) {
		if(this != &rhs)
		{
			Core::Machine::operator=(rhs);
			simConnection = rhs.simConnection;
		}
		return *this;
	}

	bool SimulationMachine::isSimulationConnected() {
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

		std::vector<models::MachineConfiguration> config;

		std::string binaryStream;

		std::stringstream outputBinary((std::ios::out | std::ios::binary));
		cereal::PortableBinaryOutputArchive archive(outputBinary);
		archive(configurations);

		binaryStream = outputBinary.str();

		Network::Message msg(Network::Protocol::SimMessageType::kSimMessageTypeConfig, binaryStream);
		sendSimulationMessage(msg);
	}

}

