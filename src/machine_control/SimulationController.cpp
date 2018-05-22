#include <network/Protocol.h>
#include "SimulationController.h"
#include "states_simulation_controller/FindProductControlState.h"
#include "ControllerNotificationEventIds.h"

namespace models {
typedef std::shared_ptr<Machine> MachinePtr;
}

namespace simulator {

/**
 * Event listener and notifier of simulation controller
 */
class NetworkEventDispatcher : public network::IServiceEventListener, public patterns::notifyobserver::Notifier {
 public:
  NetworkEventDispatcher() = default;
  ~NetworkEventDispatcher() override = default;
 private:

  void onServiceError(network::ServicePtr service, const std::string &message) override {
	//TODO: Add eventId
	//Set up the Connection Failed state event to send to the observers.
	auto event = makeNotificationForNotifier(this,
											 patterns::notifyobserver::NotifyTrigger(),
											 ControllerEvents::kNotifyEventTypeServiceError);

	//Notify observers of the error
	notifyObservers(event);
  }

  void onServiceStopped(network::ServicePtr service) override {
	// TODO: check if this is needed
  }

  void onServiceStarted(network::ServicePtr service) override {
	//Set up an event to let the observers know that connection was successful
	auto event = makeNotificationForNotifier(this,
											 patterns::notifyobserver::NotifyTrigger(),
											 ControllerEvents::kNotifyEventTypeServiceStarted);

	//Notify observers of connection success
	notifyObservers(event);
  }

};

SimulationController::SimulationController(uint16_t aMachineId)
	: Controller(aMachineId) {
  simulationNetworkComponent = std::make_shared<SimulationCommunication::SimulationNetworkComponent>();
  application = std::make_shared<SimulationApplication>(aMachineId);
}

SimulationController::~SimulationController() {
  stop();
}

void SimulationController::handleNotification(const patterns::notifyobserver::NotifyEvent &notification) {
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

	default:
	  break;
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

void SimulationController::onSimulationConfigurationsReceived(const patterns::notifyobserver::NotifyEvent &notification) {
  auto event =
	  std::make_shared<patterns::statemachine::Event>(simulationstates::kEventTypeSimulationConfigurationsReceived);

  // Set received configurations as argument
  event->setArgument(notification.getFirstArgumentAsType<models::MachinePtr>());

  scheduleEvent(event);
}

void SimulationController::registerMachine() {
  simulationNetworkComponent->sendRegisterMessage(application->getId());
}

void SimulationController::machineReady() {
  simulationNetworkComponent->sendMachineReadyMessage();
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
  networkManager.setRemotePort(network::Protocol::PORT_SIMULATION_COMMUNICATION);

  // Create the thread which the manager will run on
  clientThread = networkManager.runServiceThread();

  // Set the controller to handle notifications (notifier observer pattern) for the network
  handleNotificationsFor(*simulationNetworkComponent);

  // Create the client
  client = networkManager.createClient(simulationNetworkComponent);

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
  Controller::stop();

  // Stop the network manager
  networkManager.stop();

  // Join the client thread
  if (clientThread && clientThread->joinable()) {
	clientThread->join();
	client = network::ClientPtr();
  }
}

void SimulationController::setMachineInfo(const models::MachinePtr &machine) {
  application->setConfigurations(machine->getConfigurations());
  auto event = std::make_shared<patterns::statemachine::Event>(simulationstates::kEventTypeSimulationConfigurationsSet);
  scheduleEvent(event);
}

void SimulationController::setRemoteHost(const std::string &remoteHost) {
  networkManager.setRemoteHost(remoteHost);
}

}
