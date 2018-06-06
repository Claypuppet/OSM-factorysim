
#define BOOST_TEST_DYN_LINK

#include <memory>

#include <boost/test/unit_test.hpp>
#include <patterns/notifyobserver/Notifier.hpp>
#include <configuration_serializer/ConfigurationReader.h>

#include "../../src/production_control/Application.h"
#include "../test_helpers/MockNetwork.h"

#include "../../src/production_control/states_application/WaitForConnectionsState.h"
#include "../../src/production_control/SimulationController.h"
#include "../../src/production_control/NotificationTypes.h"

#include "../test_helpers/MockObserver.h"
#include "../../src/production_control/ConnectionHandler.h"
#include "../test_helpers/HelperFunctions.h"
#include "../../src/production_control/states_application/InOperationState.h"
#include "../../src/production_control/InfiniteBuffer.h"

BOOST_AUTO_TEST_SUITE(ProductionControlApplicationNetworkTests)

BOOST_AUTO_TEST_CASE(ProductionControlSendStartProcess) {
  std::string configurationFilePath = "./test_configs/test_config_two_machines.yaml";
  uint16_t machineIdOfMachineToTestWith = 12; // needs to be in the config

  simulation::SimulationController controller;
  BOOST_REQUIRE_NO_THROW(controller.setConfiguration(configurationFilePath));

  auto application = controller.getApplication();
  BOOST_REQUIRE(application);

  auto machine = application->getMachine(machineIdOfMachineToTestWith);
  BOOST_REQUIRE(machine);

  auto machineMock = std::make_shared<testutils::MockNetwork>();
  auto pcMock = std::make_shared<testutils::MockNetwork>();

  testutils::OnMessageFn onMessageFn = [](const network::Message &message) {
    BOOST_CHECK_EQUAL(message.getMessageType(), network::Protocol::kAppMessageTypeStartProcess);
  };

  BOOST_REQUIRE_NO_THROW(machineMock->setOnMessageFn(onMessageFn));

  BOOST_REQUIRE_NO_THROW(pcMock->startMockPCServerApplication());

  BOOST_REQUIRE_NO_THROW(machineMock->startMockMCClientApplication());

  pcMock->awaitClientConnecting();

  BOOST_REQUIRE_NO_THROW(machine->setConnection(pcMock->getConnection()));

  BOOST_REQUIRE(machine->isConnected());

  BOOST_REQUIRE_NO_THROW(machine->sendStartProcessMessage());

  machineMock->awaitMessageReceived();

  pcMock->stop();
  machineMock->stop();
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ProductionControlTestApplicationEventProcesses)

BOOST_AUTO_TEST_CASE(ProductionControlTestApplicationEventMachineRegistered) {
  auto machineNetwork = std::make_shared<testutils::MockNetwork>();

  // use the controller for loading the config and setup the application
  simulation::SimulationController controller;
  controller.setConfiguration("./test_configs/test_config_one_machine.yaml");

  // get the application from controller
  auto &application = controller.getApplication();

  // put application in the state we want to test
  auto state = std::make_shared<applicationstates::WaitForConnectionsState>(applicationstates::WaitForConnectionsState(
      *application));
  BOOST_CHECK_NO_THROW(application->setCurrentState(state));

  // start the machine control mock server
  machineNetwork->startMockMCClientApplication();

  testutils::HelperFunctions::wait(50);

  // create the notification event that a notifier class normally sends to the observer
  patterns::notifyobserver::NotifyEvent event(NotifyEventIds::eApplicationRegisterMachine);
  event.setArgument(0, (uint64_t) 0);
  event.setArgument(1, (uint16_t) 1);
  event.setArgument(2, machineNetwork->getConnection());

  // fire the notification
  BOOST_CHECK_NO_THROW(application->handleNotification(event));

  // run the context
  BOOST_CHECK_NO_THROW(application->run());


  application->stopServer();
  controller.stop();
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ProductionControlTestApplicationMachineBuffers)

BOOST_AUTO_TEST_CASE(TestBuffer) {
  std::string configurationFilePath = "./test_configs/test_config_two_machines.yaml";
  uint16_t machineIdOfMachineToTestWith = 12; // needs to be in the config

  simulation::SimulationController controller;
  BOOST_REQUIRE_NO_THROW(controller.setConfiguration(configurationFilePath));

  auto application = controller.getApplication();
  BOOST_REQUIRE(application);

  auto machine = application->getMachine(machineIdOfMachineToTestWith);
  BOOST_REQUIRE(machine);

//  std::vector<models::MachineConfigurationPtr> configs {std::make_shared<models::MachineConfiguration>()};
//  auto machine = std::make_shared<core::Machine>();

  core::InfiniteBuffer infiniteBuffer(machine, 1);
  BOOST_CHECK(infiniteBuffer.checkFreeSpaceInBuffer(UINT16_MAX));
  BOOST_CHECK(infiniteBuffer.checkAmountInBuffer(UINT16_MAX));

  core::ProductPtr product;
  BOOST_CHECK_NO_THROW(product = infiniteBuffer.takeFromBuffer());

  BOOST_REQUIRE(product);

  // Buffer with size 3
  core::Buffer limitedBuffer(machine, 1, 3);
  BOOST_CHECK(limitedBuffer.checkFreeSpaceInBuffer(3));
  BOOST_CHECK(!limitedBuffer.checkFreeSpaceInBuffer(4));

  BOOST_CHECK_THROW(limitedBuffer.takeFromBuffer(), std::runtime_error);
  BOOST_CHECK_NO_THROW(limitedBuffer.putInBuffer(product));
  BOOST_CHECK_NO_THROW(limitedBuffer.putInBuffer(product));
  BOOST_CHECK_NO_THROW(limitedBuffer.putInBuffer(product));
  BOOST_CHECK_THROW(limitedBuffer.putInBuffer(product), std::runtime_error);

  std::vector<core::ProductPtr> productList;

  BOOST_CHECK_THROW(limitedBuffer.takeFromBuffer(5), std::runtime_error);
  BOOST_CHECK_NO_THROW(productList = limitedBuffer.takeFromBuffer(3));

  BOOST_CHECK_EQUAL(productList.size(), 3);

  BOOST_CHECK(!limitedBuffer.checkAmountInBuffer(1));
}

BOOST_AUTO_TEST_CASE(TestBufferMachineLinking) {
  const std::string filePath = "./test_configs/test_config_two_machines.yaml";

  simulation::SimulationController controller;
  BOOST_REQUIRE_NO_THROW(controller.setConfiguration(filePath));

  auto machines = controller.getApplication()->getMachines();
  BOOST_REQUIRE_EQUAL(machines.size(), 2);

  { // machines[0]
    auto machine = machines[0];
    BOOST_CHECK_EQUAL(machine->getId(), 15);
    auto inputBuffers = machine->getInputBuffers();
    BOOST_REQUIRE_EQUAL(inputBuffers.size(), 2);

    { // machines[0].previousMachines
      uint16_t configurationId = 12; // is actually the productId
      auto previousMachines = machine->getPreviousMachines(configurationId);
      BOOST_REQUIRE_EQUAL(previousMachines.size(), 1);
      BOOST_CHECK_EQUAL(previousMachines.front()->getMachineId(), 0);
      BOOST_CHECK_EQUAL(previousMachines.front()->getNeededProducts(), 5);
      BOOST_CHECK(!machine->isLastInLine(configurationId));
    }

    { // machine[0].inputBuffers
      uint16_t configurationId = 12; // is actually the productId
      auto inputBuffers = machine->getInputBuffers(configurationId);
      BOOST_REQUIRE_EQUAL(inputBuffers.size(), 1);
      BOOST_CHECK_EQUAL(inputBuffers.front()->getMachineIdOfInputFor(), 0);
    }

    { // machines[0].previousMachines
      uint16_t configurationId = 88; // is actually the productId
      auto previousMachines = machine->getPreviousMachines(configurationId);
      BOOST_REQUIRE_EQUAL(previousMachines.size(), 1);
      BOOST_CHECK_EQUAL(previousMachines.front()->getMachineId(), 0);
      BOOST_CHECK_EQUAL(previousMachines.front()->getNeededProducts(), 10);
      BOOST_CHECK(!machine->isLastInLine(configurationId));
    }

    { // machine[0].inputBuffers
      uint16_t configurationId = 88; // is actually the productId
      auto inputBuffers = machine->getInputBuffers(configurationId);
      BOOST_REQUIRE_EQUAL(inputBuffers.size(), 1);
      BOOST_CHECK_EQUAL(inputBuffers.front()->getMachineIdOfInputFor(), 0);
    }
  }

  { // machines[1]
    auto machine = machines[1];
    BOOST_REQUIRE_EQUAL(machine->getId(), 75);
    auto inputBuffers = machine->getInputBuffers();
    BOOST_REQUIRE_EQUAL(inputBuffers.size(), 2);

    { // machines[1].previousMachines
      uint16_t configurationId = 12; // is actually the productId
      auto previousMachines = machine->getPreviousMachines(configurationId);
      BOOST_REQUIRE_EQUAL(previousMachines.size(), 1);
      BOOST_CHECK_EQUAL(previousMachines.front()->getMachineId(), 15);
      BOOST_CHECK_EQUAL(previousMachines.front()->getNeededProducts(), 7);
      BOOST_CHECK(machine->isLastInLine(configurationId));
    }

    { // machines[1].inputBuffers
      uint16_t configurationId = 12; // is actually the productId
      auto inputBuffers = machine->getInputBuffers(configurationId);
      BOOST_REQUIRE_EQUAL(inputBuffers.size(), 1);
      BOOST_CHECK_EQUAL(inputBuffers.front()->getMachineIdOfInputFor(), 15);
    }

    { // machines[1].previousMachines
      uint16_t configurationId = 88; // is actually the productId
      auto previousMachines = machine->getPreviousMachines(configurationId);
      BOOST_REQUIRE_EQUAL(previousMachines.size(), 1);
      BOOST_CHECK_EQUAL(previousMachines.front()->getMachineId(), 15);
      BOOST_CHECK_EQUAL(previousMachines.front()->getNeededProducts(), 8);
      BOOST_CHECK(machine->isLastInLine(configurationId));
    }

    { // machines[1].inputBuffers
      uint16_t configurationId = 88; // is actually the productId
      auto inputBuffers = machine->getInputBuffers(configurationId);
      BOOST_REQUIRE_EQUAL(inputBuffers.size(), 1);
      BOOST_CHECK_EQUAL(inputBuffers.front()->getMachineIdOfInputFor(), 15);
    }
  }
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ProductionControlApplicationHandleMessages)

BOOST_AUTO_TEST_CASE(ProductionControlApplicationHandleStatusUpdates) {
  testutils::MockObserver observer;

  const uint16_t MACHINE_ID = 12;

  // Making the notificationhandler for the observer
  testutils::NotificationHandlerFn notificationHandler = [](const patterns::notifyobserver::NotifyEvent &notification) {
    BOOST_REQUIRE(notification.getEventId() == NotifyEventIds::eApplicationRegisterMachine);
    BOOST_REQUIRE(notification.getArgumentAsType<uint16_t>(1) == MACHINE_ID);
  };

  observer.setHandleNotificationFn(notificationHandler);

  // Making the connectionhandler
  auto connectionHandler = std::make_shared<communication::ConnectionHandler>();
  connectionHandler->addObserver(observer);

  // Making network mocks
  auto mcMock = std::make_shared<testutils::MockNetwork>();
  auto pcMock = std::make_shared<testutils::MockNetwork>();

  pcMock->setConnectionHandler(connectionHandler);

  // Starting the network objects
  pcMock->startMockPCServerApplication();
  mcMock->startMockMCClientApplication();

  // Registering a machine
  network::Message message;
  message.setMessageType(network::Protocol::kAppMessageTypeRegisterMachine);
  message.setBodyObject<uint16_t>(MACHINE_ID);

  mcMock->sendMessage(message);
  pcMock->awaitMessageReceived();

  // Executing OK status update test
  message.clear();
  message.setMessageType(network::Protocol::kAppMessageTypeOK);
  message.setBodyObject<models::Machine::MachineStatus>(models::Machine::kMachineStatusIdle);

  notificationHandler = [](const patterns::notifyobserver::NotifyEvent &notification) {
    BOOST_CHECK(notification.getEventId() == NotifyEventIds::eApplicationOK);
    BOOST_CHECK(notification.getArgumentAsType<uint16_t>(1) == MACHINE_ID);
    BOOST_CHECK_EQUAL(notification.getArgumentAsType<models::Machine::MachineStatus>(2), models::Machine::kMachineStatusIdle);
  };

  observer.setHandleNotificationFn(notificationHandler);
  mcMock->sendMessage(message);
  pcMock->awaitMessageReceived();

  // Executing NOK status update test
  message.clear();
  message.setMessageType(network::Protocol::kAppMessageTypeNOK);
  message.setBodyObject<models::Machine::MachineErrorCode>(models::Machine::kMachineErrorCodeBroke);

  notificationHandler = [](const patterns::notifyobserver::NotifyEvent &notification) {
    BOOST_CHECK(notification.getEventId() == NotifyEventIds::eApplicationNOK);
    BOOST_CHECK(notification.getArgumentAsType<uint16_t>(1) == MACHINE_ID);
    BOOST_CHECK(notification.getArgumentAsType<models::Machine::MachineErrorCode>(2) == models::Machine::kMachineErrorCodeBroke);
  };

  observer.setHandleNotificationFn(notificationHandler);
  mcMock->sendMessage(message);
  pcMock->awaitMessageReceived();

  pcMock->stop();
  mcMock->stop();

}

BOOST_AUTO_TEST_CASE(ProductionControlApplicationHandleBufferUpdates){
  testutils::MockObserver observer;

  const uint16_t MACHINE_ID = 12;

  testutils::NotificationHandlerFn notificationHandler = [](const patterns::notifyobserver::NotifyEvent& notification){
    BOOST_CHECK(notification.getEventId() == NotifyEventIds::eApplicationProductTakenFromBuffer);
    BOOST_CHECK(notification.getArgumentAsType<uint16_t>(1) == MACHINE_ID);
  };

  // Making the connectionhandler
  auto connectionHandler = std::make_shared<communication::ConnectionHandler>();
  connectionHandler->addObserver(observer);

  // Making network mocks
  auto mcMock = std::make_shared<testutils::MockNetwork>();
  auto pcMock = std::make_shared<testutils::MockNetwork>();

  pcMock->setConnectionHandler(connectionHandler);

  // Starting the network objects
  pcMock->startMockPCServerApplication();
  mcMock->startMockMCClientApplication();

  // Registering a machine
  network::Message message;
  message.setMessageType(network::Protocol::kAppMessageTypeRegisterMachine);
  message.setBodyObject<uint16_t>(MACHINE_ID);

  mcMock->sendMessage(message);
  pcMock->awaitMessageReceived();

  // Executing product taken from buffer test
  message.clear();
  message.setMessageType(network::Protocol::kAppMessageTypeProductTakenFromBuffer);

  observer.setHandleNotificationFn(notificationHandler);

  mcMock->sendMessage(message);
  pcMock->awaitMessageReceived();

  observer.awaitNotificationReceived();

  notificationHandler = [](const patterns::notifyobserver::NotifyEvent& notification){
    BOOST_CHECK(notification.getEventId() == NotifyEventIds::eApplicationProductAddedToBuffer);
    BOOST_CHECK(notification.getArgumentAsType<uint16_t>(1) == MACHINE_ID);
  };

  observer.setHandleNotificationFn(notificationHandler);

  message.clear();
  message.setMessageType(network::Protocol::kAppMessageTypeProductAddedToBuffer);

  mcMock->sendMessage(message);
  pcMock->awaitMessageReceived();

  observer.awaitNotificationReceived();

  mcMock->stop();
  pcMock->stop();
}

BOOST_AUTO_TEST_CASE(ProductionControlApplicationHandleStatusNotifications) {
  simulation::SimulationController controller;

  std::string configurationFilePath = "./test_configs/test_config_two_machines.yaml";
  BOOST_REQUIRE_NO_THROW(controller.setConfiguration(configurationFilePath));

  auto application = controller.getApplication();
  BOOST_REQUIRE(application);

  auto currentState = std::make_shared<applicationstates::InOperationState>(*application);
  BOOST_REQUIRE_NO_THROW(application->setCurrentState(currentState));

  auto machine = application->getMachine(12);
  BOOST_REQUIRE(machine);

  { // Scheduling notification and handle events
    patterns::notifyobserver::NotifyEvent notification(NotifyEventIds::eApplicationOK);
    BOOST_REQUIRE_NO_THROW(notification.setArgument(0, (uint64_t) 0)); // time
    BOOST_REQUIRE_NO_THROW(notification.setArgument(1, (uint16_t) 12)); // machine id
    BOOST_REQUIRE_NO_THROW(notification.setArgument(2, core::Machine::MachineStatus::kMachineStatusIdle)); // status update
    BOOST_REQUIRE_NO_THROW(application->handleNotification(notification));
    BOOST_REQUIRE_NO_THROW(application->run());
  }

  BOOST_CHECK_EQUAL(machine->getStatus(), core::Machine::MachineStatus::kMachineStatusIdle);

  { // Scheduling notification and handle events
    patterns::notifyobserver::NotifyEvent notification(NotifyEventIds::eApplicationOK);
    BOOST_REQUIRE_NO_THROW(notification.setArgument(0, (uint64_t) 0)); // time
    BOOST_REQUIRE_NO_THROW(notification.setArgument(1, (uint16_t) 12)); // machine id
    BOOST_REQUIRE_NO_THROW(notification.setArgument(2, core::Machine::MachineStatus::kMachineStatusConfiguring)); // status update
    BOOST_REQUIRE_NO_THROW(application->handleNotification(notification));
    BOOST_REQUIRE_NO_THROW(application->run());
  }

  BOOST_CHECK(machine->getStatus() == core::Machine::MachineStatus::kMachineStatusConfiguring);

  { // Scheduling notification and handle events
    patterns::notifyobserver::NotifyEvent notification(NotifyEventIds::eApplicationOK);
    BOOST_REQUIRE_NO_THROW(notification.setArgument(0, (uint64_t) 0)); // time
    BOOST_REQUIRE_NO_THROW(notification.setArgument(1, (uint16_t) 12)); // machine id
    BOOST_REQUIRE_NO_THROW(notification.setArgument(2, core::Machine::MachineStatus::kMachineStatusProcessingProduct)); // status update
    BOOST_REQUIRE_NO_THROW(application->handleNotification(notification));
    BOOST_REQUIRE_NO_THROW(application->run());
  }

  BOOST_CHECK(machine->getStatus() == core::Machine::MachineStatus::kMachineStatusProcessingProduct);

  { // Scheduling notification and handle events
    patterns::notifyobserver::NotifyEvent notification(NotifyEventIds::eApplicationOK);
    BOOST_REQUIRE_NO_THROW(notification.setArgument(0, (uint64_t) 0)); // time
    BOOST_REQUIRE_NO_THROW(notification.setArgument(1, (uint16_t) 12)); // machine id
    BOOST_REQUIRE_NO_THROW(notification.setArgument(2, core::Machine::MachineStatus::kMachineStatusIdle)); // status update
    BOOST_REQUIRE_NO_THROW(application->handleNotification(notification));
    BOOST_REQUIRE_NO_THROW(application->run());
  }

  BOOST_CHECK(machine->getStatus() == core::Machine::MachineStatus::kMachineStatusIdle);


  { // Scheduling notification and handle events
    patterns::notifyobserver::NotifyEvent notification(NotifyEventIds::eApplicationNOK);
    BOOST_REQUIRE_NO_THROW(notification.setArgument(0, (uint64_t) 0)); // time
    BOOST_REQUIRE_NO_THROW(notification.setArgument(1, (uint16_t) 12)); // machine id
    BOOST_REQUIRE_NO_THROW(notification.setArgument(2, models::Machine::MachineErrorCode::kMachineErrorCodeBroke)); // error code
    BOOST_REQUIRE_NO_THROW(application->handleNotification(notification));
    BOOST_REQUIRE_NO_THROW(application->run());
  }

  BOOST_CHECK(machine->getStatus() == core::Machine::MachineStatus::kMachineStatusBroken);
}

BOOST_AUTO_TEST_SUITE_END()

