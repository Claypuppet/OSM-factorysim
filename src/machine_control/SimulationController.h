//
// Created by hqnders on 20/04/18.
//

#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONCONTROLLER_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONCONTROLLER_H

#include <network/Manager.h>
#include <patterns/notifyobserver/Observer.hpp>
#include "SimulationNetworkComponent.h"
#include "Controller.h"
#include "SimulationApplication.h"

namespace Simulator {

    class SimulationController
            : public Core::Controller,
              public Patterns::Statemachine::Context,
              public Patterns::NotifyObserver::Observer {
    public:
        SimulationController();
        virtual ~SimulationController() = default;

        void run() override;

		void execute();

		void handleNotification(const Patterns::NotifyObserver::NotifyEvent &notification) override;

	private:
		bool executing;

		ThreadPtr clientThread;
		Network::Manager networkManager;
        Network::ClientPtr client;

		void setupNetwork();
	};
}


#endif //PRODUCTION_LINE_CONTROL_SIMULATIONCONTROLLER_H
