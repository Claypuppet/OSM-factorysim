//
// Created by don on 15-5-18.
//

#include <boost/test/unit_test.hpp>

#include <models/Configuration.h>
#include <utils/time/Time.h>

#include "../test_helpers/MockNetwork.h"
#include "../../src/machine_control/Application.h"
#include "../test_helpers/MockObserver.h"
#include "../machine_control/SimulationController.h"
#include "state_inclusions.h"
#include "../test_helpers/HelperFunctions.h"

BOOST_AUTO_TEST_SUITE(MachineControlApplicationTests)

BOOST_AUTO_TEST_CASE(MachineControlConnectToInitialize) {
  auto mockNetwork = std::make_shared<testutils::MockNetwork>();
  mockNetwork->startMockPCServerApplication();

  machinecore::Application application(1);
  BOOST_CHECK_NO_THROW(application.setStartState());

  auto event = std::make_shared<applicationstates::Event>(applicationstates::kEventTypeConnected);

  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<applicationstates::ConnectState>(application.getCurrentState()), true);

  BOOST_CHECK_NO_THROW(application.scheduleEvent(event));

  BOOST_CHECK_NO_THROW(application.run());

  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<applicationstates::Initialize>(application.getCurrentState()), true);

  testutils::HelperFunctions::wait(50);
}

BOOST_AUTO_TEST_CASE(MachineControlInitializeToIdle) {
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
  std::vector<models::MachineConfigurationPtr> confVector;
  auto config0 = std::make_shared<models::MachineConfiguration>(0);
  confVector.push_back(config0);

  // Set the configurations to the application
  BOOST_CHECK_NO_THROW(application.getMachine()->setConfigurations(confVector));

  // Create a ReceivedConfig event and attach the configurations to it
  auto event = std::make_shared<patterns::statemachine::Event>(applicationstates::kEventTypeReconfigure);
  BOOST_CHECK_NO_THROW(event->setArgument<uint16_t>(0));

  // Schedule the event
  BOOST_CHECK_NO_THROW(application.scheduleEvent(event));

  // Run the application
  BOOST_CHECK_NO_THROW(application.run());

  // Check if the application reached it's ConfigureState (prepare configure)
  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<applicationstates::ConfigureState>(application.getCurrentState()), true);

  BOOST_CHECK_NO_THROW(application.run());
  // Check if the application reached it's ConfigureState (configure)
  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<applicationstates::ConfigureState>(application.getCurrentState()), true);

  BOOST_CHECK_NO_THROW(application.run());
  // Check if the application reached it's ConfigureState (selftesting)
  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<applicationstates::ConfigureState>(application.getCurrentState()), true);

  BOOST_CHECK_NO_THROW(application.run());
  // Check if the application reached it's IdleState
  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<applicationstates::IdleState>(application.getCurrentState()), true);
}

BOOST_AUTO_TEST_CASE(MachineControlRunCycle) {
  simulator::SimulationApplication application(1);

  BOOST_CHECK_NO_THROW(simulator::SimulationMachine::setCanBreak(false));

  auto state = std::make_shared<applicationstates::IdleState>(applicationstates::IdleState(application));
  BOOST_CHECK_NO_THROW(application.setCurrentState(state));

  patterns::notifyobserver::NotifyEvent event(machinecore::NotifyEventType::kNotifyEventTypeStartProcess);
  BOOST_CHECK_NO_THROW(application.handleNotification(event));

  BOOST_CHECK_NO_THROW(application.run()); // process request received
  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<machinestates::TakeProductState>(application.getMachine()->getCurrentState()), true);
  BOOST_CHECK_NO_THROW(application.run()); // product is taken in
  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<machinestates::ProcessProductState>(application.getMachine()->getCurrentState()), true);
  BOOST_CHECK_NO_THROW(application.run()); // product is processed
  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<machinestates::TakeOutProductState>(application.getMachine()->getCurrentState()), true);
  BOOST_CHECK_NO_THROW(application.run()); // product is taken out
  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<applicationstates::IdleState>(application.getCurrentState()), true);
}

BOOST_AUTO_TEST_CASE(MachineControlConfigCycle) {
  auto mockNetwork = std::make_shared<testutils::MockNetwork>();
  mockNetwork->startMockPCServerApplication();

  simulator::SimulationApplication application(1);
  BOOST_CHECK_NO_THROW(application.setupNetwork());

  BOOST_CHECK_NO_THROW(simulator::SimulationMachine::setCanBreak(false));


  auto state = std::make_shared<applicationstates::IdleState>(applicationstates::IdleState(application));
  BOOST_CHECK_NO_THROW(application.setCurrentState(state));

  std::vector<models::MachineConfigurationPtr> confVector;
  auto config0 = std::make_shared<models::MachineConfiguration>(0);
  confVector.push_back(config0);
  BOOST_CHECK_NO_THROW(application.getMachine()->setConfigurations(confVector));

  patterns::notifyobserver::NotifyEvent
      notification(machinecore::NotifyEventType::kNotifyEventTypeConfigure);
  BOOST_CHECK_NO_THROW(notification.addArgument<uint16_t>(0));

  BOOST_CHECK_NO_THROW(application.handleNotification(notification));

  BOOST_CHECK_NO_THROW(application.run()); // configure request, will start machine in prepare configure
  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<machinestates::PrepareConfiguration>(application.getMachine()->getCurrentState()), true);
  BOOST_CHECK_NO_THROW(application.run()); // prepare will transition to configure
  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<machinestates::ConfiguringState>(application.getMachine()->getCurrentState()), true);
  BOOST_CHECK_NO_THROW(application.run()); // configure will transition to selftest
  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<machinestates::SelfTestState>(application.getMachine()->getCurrentState()), true);
  BOOST_CHECK_NO_THROW(application.run()); // sefltest is done, app will transition to idle
  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<applicationstates::IdleState>(application.getCurrentState()), true);

  testutils::HelperFunctions::wait(50);
}

BOOST_AUTO_TEST_CASE(MachineControlBreakingDuringConfig){
  simulator::SimulationApplication application(1);

  auto state = std::make_shared<applicationstates::IdleState>(applicationstates::IdleState(application));
  BOOST_CHECK_NO_THROW(application.setCurrentState(state));

  patterns::notifyobserver::NotifyEvent event(machinecore::NotifyEventType::kNotifyEventTypeStartProcess);
  BOOST_CHECK_NO_THROW(application.handleNotification(event));

  BOOST_CHECK_NO_THROW(application.run());

  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<applicationstates::InOperationState>(application.getCurrentState()), true);

  auto stateEvent = std::make_shared<machinestates::Event>(machinestates::kEventTypeMachineBroke);
  BOOST_CHECK_NO_THROW(application.getMachine()->scheduleEvent(stateEvent));

  BOOST_CHECK_NO_THROW(application.run());

  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<applicationstates::BrokenState>(application.getCurrentState()),true);
}

BOOST_AUTO_TEST_CASE(MachineControlMachineBreaking){
  BOOST_CHECK_NO_THROW(simulator::SimulationMachine::setCanBreak(true));
  utils::Time::getInstance().setType(utils::TimeType::customTime);
  utils::Time::getInstance().reset();

  uint16_t nTests = 1000;
  uint16_t nFailures = 0;


  uint16_t meanTimeBetweenFailureInHours = 250;
  std::vector<models::PreviousMachinePtr> previousMachines;
  previousMachines.push_back(std::make_shared<models::PreviousMachine>());
  models::MachineConfigurationPtr configuration = std::make_shared<models::MachineConfiguration>(1, 1, 1, 1, meanTimeBetweenFailureInHours, 1, 1, previousMachines);

  uint64_t millisecondsInHour = 3600000;

  for(uint16_t i = 0; i < nTests; ++i) {
    simulator::SimulationApplication application(1);

    application.getMachine()->setCurrentConfiguration(configuration);

    application.getMachine()->configure();

    for (uint16_t j = 0; j < meanTimeBetweenFailureInHours; ++j) {
      if (application.getMachine()->checkBroken()) {
        ++nFailures;
      }
      utils::Time::getInstance().increaseCurrentTime(millisecondsInHour);
    }

    utils::Time::getInstance().reset();
  }

  BOOST_CHECK(nFailures > 0.9*nTests && nFailures < 1.1*nTests);
  BOOST_CHECK_NO_THROW(simulator::SimulationMachine::setCanBreak(false));
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
  machineNetwork->sendResponseNOK(models::Machine::kMachineErrorCodeBroke);
  productionServer->awaitMessageReceived();

  productionServer->stopServer();
  machineEndpoint->stopClient();

}

BOOST_AUTO_TEST_CASE(MachineControlHandleStartProcess) {
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

  auto machineControl = std::make_shared<testutils::MockNetwork>();
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

BOOST_AUTO_TEST_CASE(MachineControlHandleConfigReceived) {
  testutils::MockObserver mockObserver;

  testutils::NotificationHandlerFn notificationHandler = [](const patterns::notifyobserver::NotifyEvent &event) {
    BOOST_CHECK(event.getEventId() == machinecore::kNotifyEventTypeConfigure);
  };

  BOOST_REQUIRE_NO_THROW(mockObserver.setHandleNotificationFn(notificationHandler));

  auto networkComponent = std::make_shared<Communication::NetworkComponent>();
  BOOST_REQUIRE_NO_THROW(networkComponent->addObserver(mockObserver));

  auto pcMock = std::make_shared<testutils::MockNetwork>();
  auto mcMock = std::make_shared<testutils::MockNetwork>();

  mcMock->setConnectionHandler(networkComponent);

  BOOST_REQUIRE_NO_THROW(pcMock->startMockPCServerApplication());

  mcMock->startMockMCClientApplication();
  pcMock->awaitConnection();
  network::Message message(network::Protocol::kAppMessageTypeReconfigure);
  message.setBodyObject<uint16_t>(2);

  BOOST_REQUIRE_NO_THROW(pcMock->sendMessage(message));

  mockObserver.awaitNotificationReceived();

  pcMock->stopServer();
  mcMock->stopClient();
}

// Einde public method tests
BOOST_AUTO_TEST_SUITE_END()