//
// Created by hqnders on 20/04/18.
//

#include "SimulationController.h"
#include "states_simulation/FindProductControlState.h"
#include <network/Client.h>

namespace Simulator {

	/**
	 * Network service event dispatcher, handles service callbacks
	 */
	class NetworkEventDispatcher : public Network::IServiceEventListener, public Patterns::NotifyObserver::Notifier {
	public:
		NetworkEventDispatcher() = default;
		~NetworkEventDispatcher() override = default;
	private:
        /**
         * Handles errors sent by services.
         * @param service The service which reported the error.
         * @param message The error message.
         */
		void onServiceError(Network::ServicePtr service, const std::string &message) override {
		    //Set up the Connection Failed state event to send to the observers.
			auto e = std::make_shared<SimulationStates::Event>(SimulationStates::Event(SimulationStates::kEventTypeConnectionFailed));

			//Make an empty trigger
			Patterns::NotifyObserver::NotifyTrigger t;

			//Notify observers of the error
			notifyObservers(makeNotificationForNotifier(this, t, e));
		}

		void onServiceStopped(Network::ServicePtr service) override {
			// TODO: check if this is needed
		}

		/**
		 * Called on successful service connection.
		 * @param service The service which connected.
		 */
		void onServiceStarted(Network::ServicePtr service) override {
		    //Set up an event to let the observers know that connection was successful
			auto e = std::make_shared<SimulationStates::Event>(SimulationStates::kEventTypeConnected);

			//Make an empty trigger
			Patterns::NotifyObserver::NotifyTrigger t;

			//Notify observers of connection success
            notifyObservers(makeNotificationForNotifier(this, t, e));
		}

	};

	/**
	 * On every notification, checks if a state event is present and adds it to the event queue.
	 * @param notification The received notification.
	 */
	void SimulationController::handleNotification(const Patterns::NotifyObserver::NotifyEvent &notification) {
	    //Get the state event out of the notification
        auto e = notification.getStateEvent();

        //Schedule the event on existence
        if(e) {
            scheduleEvent(e);
        }
	}

	SimulationController::SimulationController(const Models::Machine& aMachineInfo)
            : Controller(aMachineInfo), executing(false) {
	}

    void SimulationController::setupNetwork(){
		clientThread = networkManager.runServiceThread();

		SimulationCommunication::SimulationNetworkComponent connectionHandler;
		handleNotificationsFor(connectionHandler);

		client = networkManager.createClient(std::make_shared<SimulationCommunication::SimulationNetworkComponent>(connectionHandler));

		auto eventDispatcherPtr = std::make_shared<NetworkEventDispatcher>();
		client->setServiceEventListener(eventDispatcherPtr);
		handleNotificationsFor(*eventDispatcherPtr);

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

    void SimulationController::registerMachine() {
	    //TODO: Implementeer functionaliteit om te registreren hier
        //MachineID is opgehaald door application.getMachineInfo().getId()
    }

	void SimulationController::setRemoteHost(const std::string &remoteHost) {
		networkManager.setRemoteHost(remoteHost);
	}
}
