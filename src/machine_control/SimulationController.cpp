//
// Created by hqnders on 20/04/18.
//

#include "SimulationController.h"
#include "states_simulation/InitializeSimulationState.h"
#include <network/Client.h>

namespace Simulator {
	void SimulationController::handleNotification(const Patterns::NotifyObserver::NotifyEvent &notification) {
		// TODO: add notification (state event) to event queue
	}

	SimulationController::SimulationController() : executing(false) {
	}

	void SimulationController::setupNetwork(){
		clientThread = networkManager.runServiceThread();

		SimulationCommunication::SimulationNetworkComponent connectionHandler;
		handleNotificationsFor(connectionHandler);

		client = networkManager.createClient(std::make_shared<SimulationCommunication::SimulationNetworkComponent>(connectionHandler));
		client->start();
	}

	void SimulationController::execute() {
		executing = true;
		setStartState();

		while(executing){
			run();
		}
	}

	void SimulationController::setStartState()
	{
		auto startState = std::make_shared<SimulationStates::InitializeSimulationState>(*this);
		setCurrentState(startState);
	}

	const bool SimulationController::isConnected()  {
		return (client && client->isRunning() && client->getConnection() && client->getConnection()->isConnected());
	}
}
