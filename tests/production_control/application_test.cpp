//
// Not created by Henk on 27-08-1783
//
#define BOOST_TEST_DYN_LINK

#include <memory>
#include <climits>

#include <boost/test/unit_test.hpp>
#include <patterns/notifyobserver/Notifier.hpp>

#include "../../src/production_control/Application.h"
#include "../test_helpers/MockNetwork.h"

#include "../../src/production_control/states_application/WaitForConnectionsState.h"
#include "../../src/production_control/SimulationController.h"
#include "../../src/production_control/NotificationTypes.h"
#include "../../src/machine_control/Machine.h"
#include "../../src/production_control/Machine.h"

#include "../../src/production_control/Buffer.h"
#include "../../src/production_control/Product.h"
#include "../test_helpers/MockObserver.h"
#include "../../src/production_control/AppConnectionHandler.h"
#include "../test_helpers/HelperFunctions.h"

BOOST_AUTO_TEST_SUITE(ProductionControlApplicationNetworkTests)

BOOST_AUTO_TEST_CASE(ProductionControlSendStartProcess)
{
  core::MachinePtr machine = std::make_shared<core::Machine>(models::Machine(12, "test_machine"));

  auto machineMock  = std::make_shared<testutils::MockNetwork>();
  auto pcMock = std::make_shared<testutils::MockNetwork>();

  testutils::OnMessageFn onMessageFn = [](const Network::Message& message){
    BOOST_CHECK(message.getMessageType() == Network::Protocol::kAppMessageTypeStartProcess);
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
  controller.setConfigFromFile("./test_configs/test_config_one_machine.yaml");

  // get the application from controller
  auto &application = controller.getApplication();

  // put application in the state we want to test
  auto state = std::make_shared<ApplicationStates::WaitForConnectionsState>(ApplicationStates::WaitForConnectionsState(
      application));
  BOOST_CHECK_NO_THROW(application.setCurrentState(state));

  testutils::HelperFunctions::wait(50);

  // start the machine control mock server
  machineNetwork->startMockMCClientApplication();

  // create the notification event that a notifier class normally sends to the observer
  patterns::NotifyObserver::NotifyEvent event(NotifyEventIds::eApplicationRegisterMachine);
  event.setArgument(0, (uint16_t) 1);
  event.setArgument(1, machineNetwork->getConnection());

  // fire the notification
  BOOST_CHECK_NO_THROW(application.handleNotification(event));

  // run the context
  BOOST_CHECK_NO_THROW(application.run());

}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(ProductionControlTestApplicationMachineBuffers)

BOOST_AUTO_TEST_CASE(TestBuffer) {
  core::Buffer infiniteBuffer;
  BOOST_CHECK(infiniteBuffer.checkFreeSpaceInBuffer(UINT16_MAX));
  BOOST_CHECK(infiniteBuffer.checkAmountInBuffer(UINT16_MAX));

  core::ProductPtr product;
  BOOST_CHECK_NO_THROW(product = infiniteBuffer.takeFromBuffer());

  BOOST_REQUIRE(product);

  // Buffer with size 3
  core::Buffer limitedBuffer(3);
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

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ProductionControlApplicationHandleMessages)

BOOST_AUTO_TEST_CASE(ProductionControlApplicationHandleStatusUpdates)
{
  testutils::MockObserver observer;

  // Making the notificationhandler for the observer
  testutils::NotificationHandlerFn notificationHandler = [](const patterns::NotifyObserver::NotifyEvent& notification){
    BOOST_REQUIRE(notification.getEventId() == NotifyEventIds::eApplicationRegisterMachine);
    BOOST_REQUIRE(notification.getArgumentAsType<uint16_t>(0) == 12);
  };

  observer.setHandleNotificationFn(notificationHandler);

  // Making the connectionhandler
  auto connectionHandler = std::make_shared<core::AppConnectionHandler>();
  connectionHandler->addObserver(observer);

  // Making network mocks
  auto mcMock = std::make_shared<testutils::MockNetwork>();
  auto pcMock = std::make_shared<testutils::MockNetwork>();

  pcMock->setConnectionHandler(connectionHandler);

  // Starting the network objects
  pcMock->startMockPCServerApplication();
  mcMock->startMockMCClientApplication();

  // Registering a machine
  Network::Message message(Network::Protocol::kAppMessageTypeRegisterMachine, "12");

  mcMock->sendMessage(message);
  pcMock->awaitMessageReceived();

  // Executing Ready status update test
  message.clear();
  message.setMessageType(Network::Protocol::kAppMessageTypeReady);

  notificationHandler = [](const patterns::NotifyObserver::NotifyEvent& notification){
    BOOST_CHECK(notification.getEventId() == NotifyEventIds::eApplicationMachineReady);
    BOOST_CHECK(notification.getArgumentAsType<uint16_t>(0) == 12);
  };

  observer.setHandleNotificationFn(notificationHandler);
  mcMock->sendMessage(message);
  pcMock->awaitMessageReceived();

  // Executing started initialise status update test
  message.clear();
  message.setMessageType(Network::Protocol::kAppMessageTypeStartedInitialize);

  notificationHandler = [](const patterns::NotifyObserver::NotifyEvent& notification){
    BOOST_CHECK(notification.getEventId() == NotifyEventIds::eApplicationStartInit);
    BOOST_CHECK(notification.getArgumentAsType<uint16_t>(0) == 12);
  };

  observer.setHandleNotificationFn(notificationHandler);
  mcMock->sendMessage(message);
  pcMock->awaitMessageReceived();

  // Executing start process status update test
  message.clear();
  message.setMessageType(Network::Protocol::kAppMessageTypeStartProcess);

  notificationHandler = [](const patterns::NotifyObserver::NotifyEvent& notification){
    BOOST_CHECK(notification.getEventId() == NotifyEventIds::eApplicationStartProcessing);
    BOOST_CHECK(notification.getArgumentAsType<uint16_t>(0) == 12);
  };

  observer.setHandleNotificationFn(notificationHandler);
  mcMock->sendMessage(message);
  pcMock->awaitMessageReceived();

  // Executing done processing status update test
  message.clear();
  message.setMessageType(Network::Protocol::kAppMessageTypeDoneProcessing);

  notificationHandler = [](const patterns::NotifyObserver::NotifyEvent& notification){
    BOOST_CHECK(notification.getEventId() == NotifyEventIds::eApplicationDoneProcessing);
    BOOST_CHECK(notification.getArgumentAsType<uint16_t>(0) == 12);
  };

  observer.setHandleNotificationFn(notificationHandler);
  mcMock->sendMessage(message);
  pcMock->awaitMessageReceived();

  // Executing OK status update test
  message.clear();
  message.setMessageType(Network::Protocol::kAppMessageTypeOK);

  notificationHandler = [](const patterns::NotifyObserver::NotifyEvent& notification){
    BOOST_CHECK(notification.getEventId() == NotifyEventIds::eApplicationOK);
    BOOST_CHECK(notification.getArgumentAsType<uint16_t>(0) == 12);
  };

  observer.setHandleNotificationFn(notificationHandler);
  mcMock->sendMessage(message);
  pcMock->awaitMessageReceived();

  // Executing NOK status update test
  message.clear();
  message.setMessageType(Network::Protocol::kAppMessageTypeNOK);
  message.setBody("404");

  notificationHandler = [](const patterns::NotifyObserver::NotifyEvent& notification){
    BOOST_CHECK(notification.getEventId() == NotifyEventIds::eApplicationNOK);
    BOOST_CHECK(notification.getArgumentAsType<uint16_t>(0) == 12);
    BOOST_CHECK(notification.getArgumentAsType<std::string>(1) == "404");
  };

  observer.setHandleNotificationFn(notificationHandler);
  mcMock->sendMessage(message);
  pcMock->awaitMessageReceived();

  mcMock->stop();
  pcMock->stop();
}

BOOST_AUTO_TEST_SUITE_END()

