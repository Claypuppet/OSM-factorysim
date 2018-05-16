#include <network/Protocol.h>
#include "SimulationController.h"
#include "states_simulation/FindProductControlState.h"
#include "ControllerNotificationEventIds.h"
#include "SimulationMachine.h"

namespace models {
typedef std::shared_ptr<Machine> MachinePtr;
}

namespace simulator {

/**
 * Event listener and notifier of simulation controller
 */
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
    : Controller(aMachineId), application(aMachineId), simulationNetworkComponent(), executing(false) {
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
      onTurnOnReceived();
      break;
    }

    case ControllerEvents::kNotifyEventTypeTurnOffReceived: {
      onTurnOffReceived();
      break;
    }

    case ControllerEvents::kNotifyEventTypeServiceStarted: {
      onServiceStarted();
    }

    case ControllerEvents::kNotifyEventTypeServiceError: {
      onServiceError();
    }

    default:break;
  }
}

void SimulationController::onServiceStarted() {
  auto event = std::make_shared<patterns::statemachine::Event>(simulationstates::kEventTypeConnected);
  scheduleEvent(event);
}
void SimulationController::onServiceError() {
  auto event = std::make_shared<patterns::statemachine::Event>(simulationstates::kEventTypeConnectionFailed);
  scheduleEvent(event);
}

void SimulationController::onSimulationConfigurationsReceived(const patterns::NotifyObserver::NotifyEvent &notification) {
  auto event = std::make_shared<patterns::statemachine::Event>(simulationstates::kEventTypeSimulationConfigurationsReceived);
  
  // Set received configurations as argument
  event->setArgument(notification.getFirstArgumentAsType<models::MachinePtr>()->getConfigurations());

  scheduleEvent(event);
}

void SimulationController::registerMachine() {
  simulationNetworkComponent.sendRegisterMessage(application.getId());
}

void SimulationController::machineReady() {
  simulationNetworkComponent.sendMachineReadyMessage();
}

void SimulationController::onTurnOnReceived() {
  auto event = std::make_shared<patterns::statemachine::Event>(simulationstates::kEventTypePowerOn);
  scheduleEvent(event);
}

void SimulationController::onTurnOffReceived() {
  auto event = std::make_shared<patterns::statemachine::Event>(simulationstates::kEventTypePowerOff);
  scheduleEvent(event);
}

void SimulationController::setupNetwork() {
// Set the port of the network
  networkManager.setRemotePort(Network::Protocol::PORT_SIMULATION_COMMUNICATION);

  // Create the thread which the manager will run on
  clientThread = networkManager.runServiceThread();

  // Set the controller to handle notifications (notifier observer pattern) for the network
  handleNotificationsFor(simulationNetworkComponent);

  // Create the client
  client = networkManager.createClient(std::shared_ptr<Network::IConnectionHandler>(&simulationNetworkComponent));

  // Create and set up the event dispatcher which handles events for the connection service
  auto eventDispatcherPtr = std::make_shared<NetworkEventDispatcher>();

  // Assign the event dispatcher to the client, to handle it's connection service events
  client->setServiceEventListener(eventDispatcherPtr);

  // Set the controller to handle notifications for the event dispatcher
  handleNotificationsFor(*eventDispatcherPtr);

  // Start the client
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

  // Join the client thread
  if (clientThread && clientThread->joinable()) {
    clientThread->join();
  }
}

void SimulationController::setSimulationConfigurations(std::vector<models::MachineConfiguration> simulationConfigurations) {
  application.setConfigurations(simulationConfigurations);
}

void SimulationController::setRemoteHost(const std::string &remoteHost) {
  networkManager.setRemoteHost(remoteHost);
}
}
