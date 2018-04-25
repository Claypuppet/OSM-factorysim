#include "SimulationController.h"
#include "states_simulation/FindProductControlState.h"
#include "ControllerNotificationEventIds.h"

namespace Models {
    typedef std::shared_ptr<Machine> MachinePtr;
}

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
		    //TODO: Add eventId
		    //Set up the Connection Failed state event to send to the observers.
            auto event = makeNotificationForNotifier(this, Patterns::NotifyObserver::NotifyTrigger(), ControllerEvents::kNotifyEventTypeServiceError);

            //Notify observers of the error
			notifyObservers(event);
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
            auto event = makeNotificationForNotifier(this, Patterns::NotifyObserver::NotifyTrigger(), ControllerEvents::kNotifyEventTypeServiceStarted);

			//Notify observers of connection success
            notifyObservers(event);
		}

	};

	/**
	 * Handler of every notification.
	 * @param notification The received notification.
	 */
	void SimulationController::handleNotification(const Patterns::NotifyObserver::NotifyEvent &notification) {
	    switch(notification.getEventId()){
            case ControllerEvents::kNotifyEventTypeMachineInfoReceived: {
                application.setMachineInfo(*notification.getFirstArgumentAsType<Models::MachinePtr>());
                auto e = std::make_shared<SimulationStates::Event>(SimulationStates::kEventTypeConfigReceived);
                scheduleEvent(e);
                break;
            }

            case ControllerEvents::kNotifyEventTypeTurnOnReceived :
                break;

            case ControllerEvents::kNotifyEventTypeTurnOffReceived:
                break;

            default:
                break;
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

	void SimulationController::setStartState() {
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

	void SimulationController::stop() {
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
