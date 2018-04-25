//
// Created by sven on 25-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONCONNECTIONHANDLER_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONCONNECTIONHANDLER_H


#include <network/Connection.h>
#include <patterns/notifyobserver/Notifier.hpp>
#include "SimulationController.h"


namespace Model {
    class Machine;

    class MachineConfiguration;

    typedef std::shared_ptr<Machine> MachinePtr;
    typedef std::shared_ptr<MachineConfiguration> MachineConfigurationPtr;
}

namespace Simulation {

    class SimulationConnectionHandler;

    typedef std::shared_ptr<SimulationConnectionHandler> SimulationConnectionHandlerPtr;

    class SimulationConnectionHandler :
            public Network::IConnectionHandler,
            public Patterns::NotifyObserver::Notifier {
    public:
        SimulationConnectionHandler() = default;

        virtual ~SimulationConnectionHandler() = default;

    private:
        void onConnectionFailed(Network::ConnectionPtr connection, const boost::system::error_code &error) override;

        void onConnectionEstablished(Network::ConnectionPtr connection) override;

        void
        onConnectionDisconnected(Network::ConnectionPtr connection, const boost::system::error_code &error) override;

        void onConnectionMessageReceived(Network::ConnectionPtr connection, Network::Message &message) override;


        Network::ConnectionPtr mConnection;

        /**
         * Deserialize the string (body), apply to machine. Returns true if successfully deserialized
         * @param body : body string from message
         * @param machine : machine model to fill
         * @return bool : success
         */
        bool deserializeSimulationMachineInfo(const std::string &body, Model::MachinePtr machine);

        /**
         * Handles new machine info receive
         * @param machine
         */
        void onSimulationMachineInfoReceived(const Model::Machine &machine);

        void SimulationConnectionHandler::onSimulationMachineRegister()

        /**
         * Handles machine turn on command
         */
        void onTurnOnReceived();

        /**
         * Handles machine turn off command
         */
        void onTurnOffReceived();

        /**
         * Registers new simulation machine
         */
        void onSimulationMachineRegister(Model::MachinePtr& machineSimulation);
    };
}

#endif //PRODUCTION_LINE_CONTROL_SIMULATIONCONNECTIONHANDLER_H
