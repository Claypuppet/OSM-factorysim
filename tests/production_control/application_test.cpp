//
// Not created by Henk on 27-08-1783
//
#define BOOST_TEST_DYN_LINK

#include <memory>

#include <boost/test/unit_test.hpp>
#include <patterns/notifyobserver/Notifier.hpp>

#include "../../src/production_control/Application.h"
#include "../test_helpers/MockNetwork.h"

#include "../../src/production_control/states_application/WaitForConnectionsState.h"
#include "../../src/production_control/SimulationController.h"
#include "../../src/production_control/NotificationTypes.h"
#include "../../src/machine_control/Machine.h"
#include "../../src/production_control/Machine.h"

BOOST_AUTO_TEST_SUITE(ProductionControlApplicationNetworkTests)

BOOST_AUTO_TEST_CASE(ProductionControlSendStartProcess)
{
  core::Machine machine(models::Machine(12, "test_machine"));

  auto machineMock  = std::make_shared<testutils::MockNetwork>();
  auto pcMock = std::make_shared<testutils::MockNetwork>();

  testutils::OnMessageFn onMessageFn = [](const Network::Message& message){
    BOOST_CHECK(message.getMessageType() == Network::Protocol::kAppMessageTypeStartProcess);
  };

  BOOST_REQUIRE_NO_THROW(machineMock->setOnMessageFn(onMessageFn));

  BOOST_REQUIRE_NO_THROW(pcMock->startMockPCServerApplication());
  BOOST_REQUIRE_NO_THROW(machineMock->startMockMCClientApplication());

  BOOST_REQUIRE_NO_THROW(machine.setConnection(pcMock->getConnection()));

  BOOST_REQUIRE(machine.isConnected());

  BOOST_REQUIRE_NO_THROW(machine.sendStartProcessMessage());

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
