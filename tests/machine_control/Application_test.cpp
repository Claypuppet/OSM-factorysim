//
// Created by don on 15-5-18.
//

#include <boost/test/unit_test.hpp>

#include <models/Configuration.h>

#include "../test_helpers/MockNetwork.h"
#include "../../src/machine_control/Application.h"
#include "../test_helpers/MockObserver.h"
#include "../machine_control/SimulationController.h"
#include "state_inclusions.h"


BOOST_AUTO_TEST_SUITE(MachineControlApplicationTests)

BOOST_AUTO_TEST_CASE(MachineControlConnectToReceiveConfigState) {
  auto mockNetwork = std::make_shared<testutils::MockNetwork>();
  mockNetwork->startMockPCServerApplication();

  machinecore::Application application(1);
  BOOST_CHECK_NO_THROW(application.setStartState());

  auto event = std::make_shared<applicationstates::Event>(applicationstates::kEventTypeConnected);

  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<applicationstates::ConnectState>(application.getCurrentState()), true);

  BOOST_CHECK_NO_THROW(application.scheduleEvent(event));

  BOOST_CHECK_NO_THROW(application.run());

  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<applicationstates::Initialize>(application.getCurrentState()), true);

  application.stop();
  mockNetwork->stop();
}

BOOST_AUTO_TEST_CASE(MachineControlConnectToIdle) {
  auto mockNetwork = std::make_shared<testutils::MockNetwork>();
  mockNetwork->startMockPCServerApplication();

  // Create application context
  simulator::SimulationApplication application(1);

  // Set up it's network
  BOOST_CHECK_NO_THROW(application.setupNetwork());

  // Set the application to it's initialization state
  auto state = std::make_shared<applicationstates::Initialize>(applicationstates::Initialize(application));
  BOOST_CHECK_NO_THROW(application.setCurrentState(state));

  // Check if the application is in it's initialization stage
  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<applicationstates::Initialize>(application.getCurrentState()), true);

  // Create a sample vector for configurations
  std::vector<models::MachineConfiguration> confVector;
  models::MachineConfiguration config0 = models::MachineConfiguration(0);
  confVector.push_back(config0);

  // Set the configurations to the application
  BOOST_CHECK_NO_THROW(application.getMachine()->setConfigurations(confVector));

  // Create a ReceivedConfig event and attach the configurations to it
  auto event = std::make_shared<patterns::statemachine::Event>(applicationstates::kEventTypeReceivedConfig);
  BOOST_CHECK_NO_THROW(event->setArgument<uint16_t>(0));

  // Schedule the event
  BOOST_CHECK_NO_THROW(application.scheduleEvent(event));

  // Run the application
  BOOST_CHECK_NO_THROW(application.run());

  // Check if the application reached it's IdleState
  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<applicationstates::IdleState>(application.getCurrentState()), true);

  application.stop();
  mockNetwork->stop();
}

BOOST_AUTO_TEST_CASE(MachineControlRunCycle) {
  simulator::SimulationApplication application(1);

  BOOST_CHECK_NO_THROW(simulator::SimulationMachine::setCanBreak(false));

  auto state = std::make_shared<applicationstates::IdleState>(applicationstates::IdleState(application));
  BOOST_CHECK_NO_THROW(application.setCurrentState(state));

  patterns::notifyobserver::NotifyEvent event(machinecore::NotifyEventType::kNotifyEventTypeStartProcess);
  BOOST_CHECK_NO_THROW(application.handleNotification(event));

  BOOST_CHECK_NO_THROW(application.run());

  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<applicationstates::IdleState>(application.getCurrentState()),
                    true);
}

BOOST_AUTO_TEST_CASE(MachineControlConfigCycle) {
  auto mockNetwork = std::make_shared<testutils::MockNetwork>();
  mockNetwork->startMockPCServerApplication();

  simulator::SimulationApplication application(1);
  BOOST_CHECK_NO_THROW(application.setupNetwork());

  BOOST_CHECK_NO_THROW(simulator::SimulationMachine::setCanBreak(false));


  auto state = std::make_shared<applicationstates::IdleState>(applicationstates::IdleState(application));
  BOOST_CHECK_NO_THROW(application.setCurrentState(state));

  std::vector<models::MachineConfiguration> confVector;
  models::MachineConfiguration config0 = models::MachineConfiguration(0);
  confVector.push_back(config0);
  BOOST_CHECK_NO_THROW(application.getMachine()->setConfigurations(confVector));

  patterns::notifyobserver::NotifyEvent
      notification(machinecore::NotifyEventType::kNotifyEventTypeConfigure);
  BOOST_CHECK_NO_THROW(notification.addArgument<uint16_t>(0));

  BOOST_CHECK_NO_THROW(application.handleNotification(notification));

  BOOST_CHECK_NO_THROW(application.run());

  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<applicationstates::IdleState>(application.getCurrentState()), true);

  application.stop();
  mockNetwork->stop();
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(MachineControlProductionNetworkTests)

BOOST_AUTO_TEST_CASE(MachineControlSendMachineUpdates) {
  // Create server and client
  auto machineEndpoint = std::make_shared<testutils::MockNetwork>();
  auto productionServer = std::make_shared<testutils::MockNetwork>();

  auto machineNetwork = std::make_shared<Communication::NetworkComponent>();
  machineEndpoint->setConnectionHandler(machineNetwork);

  // Start server, start client, wait for connection on server
  productionServer->startMockPCServerApplication();
  machineEndpoint->startMockMCClientApplication();
  productionServer->awaitClientConnecting();

  // prepare test on machine control when message will receive: kAppMessageTypeOK
  testutils::OnMessageFn callback = [](network::Message &message) {
    BOOST_CHECK_EQUAL(message.getMessageType(), network::Protocol::kAppMessageTypeOK);
    BOOST_CHECK_EQUAL(message.getBodyObject<models::Machine::MachineStatus>(), models::Machine::kMachineStatusConfiguring);
  };
  productionServer->setOnMessageFn(callback);
  machineNetwork->sendStatusUpdate(models::Machine::kMachineStatusConfiguring);
  productionServer->awaitMessageReceived();

  // prepare test on machine control when message will receive: kAppMessageTypeNOK
  callback = [](network::Message &message) {
    BOOST_CHECK_EQUAL(message.getMessageType(), network::Protocol::kAppMessageTypeNOK);
  };
  productionServer->setOnMessageFn(callback);
  machineNetwork->sendResponseNOK(0);
  productionServer->awaitMessageReceived();

  machineEndpoint->stop();
  productionServer->stop();
}

BOOST_AUTO_TEST_CASE(MachineControlHandleStartProcess) {
  // Deze moet opnieuw ivm gebruik van manager en client. hiervoor kan mocknetwork gebruikt worden.
  testutils::MockObserver mockObserver;

  testutils::NotificationHandlerFn notificationHandler = [](const patterns::notifyobserver::NotifyEvent &event) {
    BOOST_CHECK(event.getEventId() == machinecore::kNotifyEventTypeStartProcess);
  };

  mockObserver.setHandleNotificationFn(notificationHandler);

  auto networkComponent = std::make_shared<Communication::NetworkComponent>();
  networkComponent->addObserver(mockObserver);

  auto pcMock = std::make_shared<testutils::MockNetwork>();

  network::Manager manager;
  manager.setRemotePort(network::Protocol::PORT_PRODUCTION_COMMUNICATION);

  auto clientThread = manager.runServiceThread();
  auto client = manager.createClient(networkComponent);

  BOOST_REQUIRE_NO_THROW(pcMock->startMockPCServerApplication());

  client->start();
  pcMock->awaitConnection();
  network::Message message(network::Protocol::kAppMessageTypeStartProcess);

  BOOST_REQUIRE_NO_THROW(pcMock->sendMessage(message));

  mockObserver.awaitNotificationReceived();

  pcMock->stop();
  manager.stop();
  clientThread->join();
}

// Einde public method tests
BOOST_AUTO_TEST_SUITE_END()