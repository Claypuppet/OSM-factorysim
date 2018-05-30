//
// Not created by Henk on 27-08-1783
//
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
  std::vector<models::MachineConfigurationPtr> configs {std::make_shared<models::MachineConfiguration>()};
  auto machine = std::make_shared<core::Machine>(models::Machine(1, "", configs));

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
  std::vector<models::MachineConfigurationPtr> configs {std::make_shared<models::MachineConfiguration>()};
  auto machine = std::make_shared<core::Machine>(models::Machine(1, "", configs));
  core::InfiniteBuffer infiniteBuffer(1);
  BOOST_CHECK(infiniteBuffer.checkFreeSpaceInBuffer(UINT16_MAX));
  BOOST_CHECK(infiniteBuffer.checkAmountInBuffer(UINT16_MAX));

  core::ProductPtr product;
  BOOST_CHECK_NO_THROW(product = infiniteBuffer.takeFromBuffer());

  BOOST_REQUIRE(product);

  // Buffer with size 3
  core::Buffer limitedBuffer(machine, 3, 1);
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
  simulation::SimulationController controller;

  const std::string filePath = "./test_configs/test_config_two_machines.yaml";
  BOOST_REQUIRE_NO_THROW(controller.setConfiguration(filePath));

  auto machines = controller.getApplication()->getMachines();

  BOOST_REQUIRE_EQUAL(machines.size(), 2);
  auto machine1 = machines[0];
  auto machine2 = machines[1];

  BOOST_CHECK_EQUAL(machine1->getId(), 15);
  BOOST_CHECK_EQUAL(machine2->getId(), 75);

  auto m1Previous1 = machine1->getPreviousMachines(12);
  auto m1Previous2 = machine1->getPreviousMachines(88);
  BOOST_REQUIRE_EQUAL(m1Previous1.size(), 1);
  BOOST_CHECK_EQUAL(m1Previous1.front()->getMachineId(), 0);
  BOOST_CHECK_EQUAL(m1Previous1.front()->getNeededProducts(), 5);
  BOOST_REQUIRE_EQUAL(m1Previous2.size(), 1);
  BOOST_CHECK_EQUAL(m1Previous2.front()->getMachineId(), 0);
  BOOST_CHECK_EQUAL(m1Previous2.front()->getNeededProducts(), 10);

  auto m2Previous1 = machine2->getPreviousMachines(12);
  BOOST_REQUIRE_EQUAL(m2Previous1.size(), 1);
  BOOST_CHECK_EQUAL(m2Previous1.front()->getMachineId(), 15);
  BOOST_CHECK_EQUAL(m2Previous1.front()->getNeededProducts(), 7);
  auto m2Previous2 = machine2->getPreviousMachines(88);
  BOOST_REQUIRE_EQUAL(m2Previous2.size(), 1);
  BOOST_CHECK_EQUAL(m2Previous2.front()->getMachineId(), 15);
  BOOST_CHECK_EQUAL(m2Previous2.front()->getNeededProducts(), 8);

  auto m1InputBuffers = machine1->getInputBuffers();
  BOOST_REQUIRE_EQUAL(m1InputBuffers.size(), 2);

  auto m1InputBuffer1 = machine1->getInputBuffers(12);
  BOOST_REQUIRE_EQUAL(m1InputBuffer1.size(), 1);
  BOOST_CHECK_EQUAL(m1InputBuffer1.front()->getFromMachineId(), 0);
  auto m1InputBuffer2 = machine1->getInputBuffers(88);
  BOOST_REQUIRE_EQUAL(m1InputBuffer2.size(), 1);
  BOOST_CHECK_EQUAL(m1InputBuffer2.front()->getFromMachineId(), 0);

  auto m2InputBuffers = machine2->getInputBuffers();
  BOOST_REQUIRE_EQUAL(m2InputBuffers.size(), 2);

  auto m2InputBuffer1 = machine2->getInputBuffers(12);
  BOOST_REQUIRE_EQUAL(m2InputBuffer1.size(), 1);
  BOOST_CHECK_EQUAL(m2InputBuffer1.front()->getFromMachineId(), 15);
  auto m2InputBuffer2 = machine2->getInputBuffers(88);
  BOOST_REQUIRE_EQUAL(m2InputBuffer2.size(), 1);
  BOOST_CHECK_EQUAL(m2InputBuffer2.front()->getFromMachineId(), 15);




}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ProductionControlApplicationHandleMessages)

BOOST_AUTO_TEST_CASE(ProductionControlApplicationHandleStatusUpdates) {
  testutils::MockObserver observer;

  // Making the notificationhandler for the observer
  testutils::NotificationHandlerFn notificationHandler = [](const patterns::notifyobserver::NotifyEvent &notification) {
    BOOST_REQUIRE(notification.getEventId() == NotifyEventIds::eApplicationRegisterMachine);
    BOOST_REQUIRE(notification.getArgumentAsType<uint16_t>(1) == 12);
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
  message.setBodyObject<uint16_t>(12);

  mcMock->sendMessage(message);
  pcMock->awaitMessageReceived();

  // Executing OK status update test
  message.clear();
  message.setMessageType(network::Protocol::kAppMessageTypeOK);
  message.setBodyObject<models::Machine::MachineStatus>(models::Machine::kMachineStatusIdle);

  notificationHandler = [](const patterns::notifyobserver::NotifyEvent &notification) {
    BOOST_CHECK(notification.getEventId() == NotifyEventIds::eApplicationOK);
    BOOST_CHECK(notification.getArgumentAsType<uint16_t>(1) == 12);
    BOOST_CHECK_EQUAL(notification.getArgumentAsType<models::Machine::MachineStatus>(2), models::Machine::kMachineStatusIdle);
  };

  observer.setHandleNotificationFn(notificationHandler);
  mcMock->sendMessage(message);
  pcMock->awaitMessageReceived();

  // Executing NOK status update test
  message.clear();
  message.setMessageType(network::Protocol::kAppMessageTypeNOK);
  message.setBodyObject<uint16_t>(404);

  notificationHandler = [](const patterns::notifyobserver::NotifyEvent &notification) {
    BOOST_CHECK(notification.getEventId() == NotifyEventIds::eApplicationNOK);
    BOOST_CHECK(notification.getArgumentAsType<uint16_t>(1) == 12);
    BOOST_CHECK(notification.getArgumentAsType<uint16_t>(2) == 404);
  };

  observer.setHandleNotificationFn(notificationHandler);
  mcMock->sendMessage(message);
  pcMock->awaitMessageReceived();

  pcMock->stop();
  mcMock->stop();

}

BOOST_AUTO_TEST_CASE(ProductionControlApplicationHandleStatusNotifications) {
  //Making machines
  std::vector<core::MachinePtr> machines;
  std::vector<models::MachineConfigurationPtr> configs {std::make_shared<models::MachineConfiguration>()};
  machines.push_back(std::make_shared<core::Machine>(models::Machine(12, "machine12", configs)));
  machines.push_back(std::make_shared<core::Machine>(models::Machine(13, "machine13", configs)));
  machines.push_back(std::make_shared<core::Machine>(models::Machine(14, "machine14", configs)));

  //Making and setting up application
  core::Application app;
  app.setProductionLine(std::make_shared<models::ProductionLine>());
  BOOST_REQUIRE_NO_THROW(app.setMachines(machines));
  BOOST_REQUIRE_NO_THROW(app.setCurrentState(std::make_shared<applicationstates::InOperationState>(app)));

  { // Scheduling notification and handle events
    patterns::notifyobserver::NotifyEvent notification(NotifyEventIds::eApplicationOK);
    notification.setArgument(0, (uint64_t) 0); // time
    notification.setArgument(1, (uint16_t) 12); // machine id
    notification.setArgument(2, core::Machine::MachineStatus::kMachineStatusIdle); // status update
    app.handleNotification(notification);
    app.run();
  }

  auto machine = app.getMachine(12);

  BOOST_REQUIRE(machine);

  BOOST_CHECK(machine->getStatus() == core::Machine::MachineStatus::kMachineStatusIdle);

  { // Scheduling notification and handle events
    patterns::notifyobserver::NotifyEvent notification(NotifyEventIds::eApplicationOK);
    BOOST_REQUIRE_NO_THROW(notification.setArgument(0, (uint64_t) 0)); // time
    BOOST_REQUIRE_NO_THROW(notification.setArgument(1, (uint16_t) 12)); // machine id
    BOOST_REQUIRE_NO_THROW(notification.setArgument(2, core::Machine::MachineStatus::kMachineStatusConfiguring)); // status update
    BOOST_REQUIRE_NO_THROW(app.handleNotification(notification));
    BOOST_REQUIRE_NO_THROW(app.run());
  }

  BOOST_CHECK(machine->getStatus() == core::Machine::MachineStatus::kMachineStatusConfiguring);

  { // Scheduling notification and handle events
    patterns::notifyobserver::NotifyEvent notification(NotifyEventIds::eApplicationOK);
    BOOST_REQUIRE_NO_THROW(notification.setArgument(0, (uint64_t) 0)); // time
    BOOST_REQUIRE_NO_THROW(notification.setArgument(1, (uint16_t) 12)); // machine id
    BOOST_REQUIRE_NO_THROW(notification.setArgument(2, core::Machine::MachineStatus::kMachineStatusProcessingProduct)); // status update
    BOOST_REQUIRE_NO_THROW(app.handleNotification(notification));
    BOOST_REQUIRE_NO_THROW(app.run());
  }

  BOOST_CHECK(machine->getStatus() == core::Machine::MachineStatus::kMachineStatusProcessingProduct);

  { // Scheduling notification and handle events
    patterns::notifyobserver::NotifyEvent notification(NotifyEventIds::eApplicationOK);
    BOOST_REQUIRE_NO_THROW(notification.setArgument(0, (uint64_t) 0)); // time
    BOOST_REQUIRE_NO_THROW(notification.setArgument(1, (uint16_t) 12)); // machine id
    BOOST_REQUIRE_NO_THROW(notification.setArgument(2, core::Machine::MachineStatus::kMachineStatusIdle)); // status update
    BOOST_REQUIRE_NO_THROW(app.handleNotification(notification));
    BOOST_REQUIRE_NO_THROW(app.run());
  }

  BOOST_CHECK(machine->getStatus() == core::Machine::MachineStatus::kMachineStatusIdle);

}

BOOST_AUTO_TEST_SUITE_END()

