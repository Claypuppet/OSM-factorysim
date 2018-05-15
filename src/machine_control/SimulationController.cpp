#include <network/Protocol.h>
#include "SimulationController.h"
#include "states_simulation/FindProductControlState.h"
#include "ControllerNotificationEventIds.h"
#include "SimulationMachine.h"

namespace models {
typedef std::shared_ptr<Machine> MachinePtr;
}

namespace simulator {

class NetworkEventDispatcher : public Network::IServiceEventListener, public patterns::NotifyObserver::Notifier {
 public:
  NetworkEventDispatcher() = default;
  ~NetworkEventDispatcher() override = default;
 private:

  void onServiceError(Network::ServicePtr service, const std::string &message) override {
    //TODO: Add eventId
    //Set up the Connection Failed state event to send to the observers.
    auto event = makeNotificationForNotifier(this,
                                             patterns::NotifyObserver::NotifyTrigger(),
                                             ControllerEvents::kNotifyEventTypeServiceError);

    //Notify observers of the error
    notifyObservers(event);
  }

  void onServiceStopped(Network::ServicePtr service) override {
    // TODO: check if this is needed
  }

  void onServiceStarted(Network::ServicePtr service) override {
    //Set up an event to let the observers know that connection was successful
    auto event = makeNotificationForNotifier(this,
                                             patterns::NotifyObserver::NotifyTrigger(),
                                             ControllerEvents::kNotifyEventTypeServiceStarted);

    //Notify observers of connection success
    notifyObservers(event);
  }

};

SimulationController::SimulationController(uint16_t aMachineId)
    : Controller(aMachineId), application(aMachineId), executing(false) {
}

SimulationController::~SimulationController() {
  stop();
}

void SimulationController::handleNotification(const patterns::NotifyObserver::NotifyEvent &notification) {
  switch (notification.getEventId()) {
    case ControllerEvents::kNotifyEventTypeSimulationConfigurationsReceived: {
      onSimulationConfigurationsReceived(notification);
      break;
    }

    case ControllerEvents::kNotifyEventTypeTurnOnReceived: {
      break;
    }

    case ControllerEvents::kNotifyEventTypeTurnOffReceived: {
      break;
    }

    default:break;
  }
}

/**
 * Executed on receiving new machine configurations
 * @param notification Notification containing the new configuration(s)
 */
void SimulationController::onSimulationConfigurationsReceived(const patterns::NotifyObserver::NotifyEvent &notification) {  
  // Create a state event to advance to the next state
  auto event = std::make_shared<simulationstates::Event>(simulationstates::kEventTypeSimulationConfigurationsReceived);
  
  // Set received configurations as argument
  event->setArgument(notification.getFirstArgumentAsType<models::MachinePtr>()->getConfigurations());

  // Schedule the event in the context
  scheduleEvent(event);
}

void SimulationController::setupNetwork() {
  networkManager.setRemotePort(Network::Protocol::PORT_SIMULATION_COMMUNICATION);
  clientThread = networkManager.runServiceThread();

  SimulationCommunication::SimulationNetworkComponent connectionHandler;
  handleNotificationsFor(connectionHandler);

  client = networkManager.createClient(std::make_shared<SimulationCommunication::SimulationNetworkComponent>(
      connectionHandler));

  auto eventDispatcherPtr = std::make_shared<NetworkEventDispatcher>();
  client->setServiceEventListener(eventDispatcherPtr);
  handleNotificationsFor(*eventDispatcherPtr);

  client->start();
}

void SimulationController::setStartState() {
  auto startState = std::make_shared<simulationstates::FindProductControlState>(*this);
  setCurrentState(startState);
}

void SimulationController::execute() {
  setStartState();

  executing = true;
  while (executing) {
    run();
  }
}

void SimulationController::stop() {
  // Set the controller to inactive
  executing = false;

  // Stop the network manager
  networkManager.stop();

  if(client){
    client->stop();
  }

  // Join the client thread
  if (clientThread && clientThread->joinable()) {
    clientThread->join();
  }
}

void SimulationController::registerMachine() {
  //TODO: Implementeer functionaliteit om te registreren hier
  //MachineID is opgehaald door application.getMachineInfo().getId()
}

void SimulationController::setSimulationConfigurations(std::vector<models::MachineConfiguration> simulationConfigurations) {
  application.setConfigurations(simulationConfigurations);
}

void SimulationController::setRemoteHost(const std::string &remoteHost) {
  networkManager.setRemoteHost(remoteHost);
}
}
