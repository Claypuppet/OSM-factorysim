//
// Created by hqnders on 20/04/18.
//

#include "SimulationController.h"
#include "states_simulation/FindProductControlState.h"
#include <network/Client.h>

namespace Simulator {

	class SimulationNetworkService : public Network::IServiceEventListener, public Patterns::NotifyObserver::Notifier {
	public:
		SimulationNetworkService() = default;
		~SimulationNetworkService() override = default;
	private:
		void onServiceError(Network::ServicePtr service, const std::string &message) override {

		}

		void onServiceStopped(Network::ServicePtr service) override {

		}

		void onServiceStarted(Network::ServicePtr service) override {

		}

	};


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

	void SimulationController::setStartState()
	{
		auto startState = std::make_shared<SimulationStates::FindProductControlState>(*this);
		setCurrentState(startState);
	}

	void SimulationController::execute() {
		setStartState();

		executing = true;
		while(executing){
			run();
		}
	}

	void SimulationController::stop(){
		executing = false;
		networkManager.stop();
		clientThread->join();
	}

	void SimulationController::setRemoteHost(const std::string &remoteHost) {
		networkManager.setRemoteHost(remoteHost);
	}
}
