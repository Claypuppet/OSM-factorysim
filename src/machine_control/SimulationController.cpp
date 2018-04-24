//
// Created by hqnders on 20/04/18.
//

#include "SimulationController.h"
#include <network/Client.h>

namespace Simulator {
	void SimulationController::handleNotification(const Patterns::NotifyObserver::NotifyEvent &notification) {
		// TODO: add notification (state event) to event queue

	}

	void SimulationController::run() {
		Context::run();
	}

	SimulationController::SimulationController() : executing(false) {
	}

	void SimulationController::setupNetwork(){
		clientThread = networkManager.runServiceThread();

		SimulationCommunication::SimulationNetworkComponent connectionHandler;
		handleNotificationsFor(connectionHandler);

		client = networkManager.createClient(std::make_shared<SimulationCommunication::SimulationNetworkComponent>(connectionHandler));

	}

	void SimulationController::execute() {
		// TODO: set first state
		executing = true;


		setupNetwork();

		// This should be done in a state
		client->start();


		while(executing)
			run();
	}
}
