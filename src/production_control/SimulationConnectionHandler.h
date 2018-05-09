//
// Created by sven on 25-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONCONNECTIONHANDLER_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONCONNECTIONHANDLER_H


#include <network/Connection.h>
#include <patterns/notifyobserver/Notifier.hpp>
#include <models/Configuration.h>
#include <models/Machine.h>

#include "SimulationController.h"


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


        /**
       * If message is received check for type and tries to fire an event with messageBody and connectionPointer
         * Possible Events:
         * MCsim -> PCsim kSimMessageTypeRegister: Register external simulationmachine to receive future data for simulations
       * @param connection : connection to listen to
       * @param message : incomming message
       */
        void onConnectionMessageReceived(Network::ConnectionPtr connection, Network::Message &message) override;


        Network::ConnectionPtr mConnection;

        /**
         * Deserialize the string (body), apply to machine. Returns true if successfully deserialized
         * @param body : body string from message
         * @param machine : machine model to fill
         * @return bool : success
         */
        bool deserializeSimulationMachineInfo(const std::string &body, Models::MachinePtr machine);

        /**
         * Handles new machine info receive
         * @param machine
         */
        void onSimulationMachineInfoReceived(const Models::Machine &machine);


        void sendConfigureMachine(uint16_t m, Network::ConnectionPtr &connection);

        /**
         * Handles incomming messages for registering machines
         * @param message : The body of the incomming message
         * @param connection : The connection that send the message
         */
        void handleRegisterMachine(const std::string& message, Network::ConnectionPtr connection);
    };
}

#endif //PRODUCTION_LINE_CONTROL_SIMULATIONCONNECTIONHANDLER_H
