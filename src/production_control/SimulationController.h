//
// Created by sven on 22-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONCONTROLLER_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONCONTROLLER_H

#include <network/Server.h>
#include <patterns/notifyobserver/Observer.hpp>
#include "Controller.h"



namespace Core {
    class SimulationController : public Controller, public Patterns::NotifyObserver::Observer {
    public:
        SimulationController();
        SimulationController(const std::string&);

        void handleNotification(const Patterns::NotifyObserver::NotifyEvent &notification) override;

        virtual ~SimulationController() = default;

        void addMachine(Core::Machine& m);
        Core::MachinePtr getMachine(uint16_t id);

        void sendConfigureMachine(uint16_t m, Network::ConnectionPtr &connection);

		void setupNetwork();
		void execute();


		void setConfigFromFile(const std::string &);

	private:
		void setStartState();

		void handleRegisterMachine(const Patterns::NotifyObserver::NotifyEvent &notification);
		void registerMachine(uint16_t machineId, const Network::ConnectionPtr connection);

		void sendTurnOnMachine(uint16_t m);
		void sendTurnOffMachine(uint16_t m);
        Network::Manager networkManager;
        ThreadPtr serverThread;
        Network::ServerPtr server;
        std::vector<Core::Machine> machines;
        bool executing;
        std::string configFile;


	};
}

#endif //PRODUCTION_LINE_CONTROL_SIMULATIONCONTROLLER_H
