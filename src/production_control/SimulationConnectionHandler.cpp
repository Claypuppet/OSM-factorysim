//
// Created by sven on 25-4-18.
//

#include <network/Protocol.h>
#include "SimulationConnectionHandler.h"

namespace Simulation {
    void SimulationConnectionHandler::onConnectionFailed(Network::ConnectionPtr connection,
                                                         const boost::system::error_code &error) {
        IConnectionHandler::onConnectionFailed(connection, error);
        std::cout << "not connected" << std::endl;
    }

    void SimulationConnectionHandler::onConnectionEstablished(Network::ConnectionPtr connection) {
        mConnection = connection;
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
            case Network::Protocol::kSimMessageTypeRegister :
                Model::MachinePtr machineSimulation;
                if (deserializeSimulationMachineInfo(message.mBody, machineSimulation)) {
                    onSimulationMachineRegister(machineSimulation);
                }
                break;
        }
    }

    bool SimulationConnectionHandler::deserializeSimulationMachineInfo(const std::string &string,
                                                                       Model::MachinePtr machine) {
//		std::stringstream binaryStream((std::ios::in | std::ios::binary));
//		binaryStream.str(string);
//		cereal::PortableBinaryInputArchive archive(binaryStream);
//		archive(machine);
        return !!machine;
    }

    void SimulationConnectionHandler::onSimulationMachineInfoReceived(const Model::Machine &machine) {
//		auto machinePtr = std::make_shared<Model::Machine>(machine);


    }

    void SimulationConnectionHandler::onSimulationMachineRegister(Model::MachinePtr& machineSimulation) {
        //TODO registreer externe machine als SimulationMachine
    }

    void SimulationConnectionHandler::turnOnMachine() {
        //TODO zet machine aan


    }

    void SimulationConnectionHandler::turnOffMachine() {
        //TODO zet machine uit

    }
    void SimulationConnectionHandler::turnOnMachine() {

    }
}