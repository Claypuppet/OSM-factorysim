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

void SimulationController::handleNotification(const patterns::NotifyObserver::NotifyEvent &notification) {
  switch (notification.getEventId()) {
    case ControllerEvents::kNotifyEventTypeMachineInfoReceived: {
      onMachineInfoReceived(notification);
      break;
    }

    case ControllerEvents::kNotifyEventTypeTurnOnReceived :break;

    case ControllerEvents::kNotifyEventTypeTurnOffReceived:break;

    default:break;
  }
}

/**
 * Executed on receiving new machine configurations
 * @param notification Notification containing the new configuration(s)
 */
void SimulationController::onMachineInfoReceived(const patterns::NotifyObserver::NotifyEvent &notification) {

  // Get the machien model from the notification's arguments
  models::Machine &machineModel = *notification.getFirstArgumentAsType<models::MachinePtr>();

  // Set the application's configurations to the machine model's configurations
  application.setConfigurations(machineModel.getConfigurations());

  // Create a state event to advance to the next state
  auto e = std::make_shared<simulationstates::Event>(simulationstates::kEventTypeConfigReceived);

  // Schedule the event in the context
  scheduleEvent(e);
}

SimulationController::SimulationController(uint16_t aMachineId)
    : Controller(aMachineId), application(aMachineId), executing(false) {
}

SimulationController::~SimulationController() {
  stop();
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

  // Join the client thread
  if (clientThread->joinable()) {
    clientThread->join();
  }
}

void SimulationController::setRemoteHost(const std::string &remoteHost) {
  networkManager.setRemoteHost(remoteHost);
}
}
