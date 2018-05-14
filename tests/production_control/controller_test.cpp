/*
 * Test Production Control - Controller
 */

// http://www.boost.org/doc/libs/1_60_0/libs/test/doc/html/boost_test/adv_scenarios/shared_lib_customizations/entry_point.html

#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <network/Client.h>

#include <patterns/notifyobserver/Notifier.hpp>
#include <network/Protocol.h>

#include "../test_helpers/MockNetwork.h"
#include "../production_control/SimulationController.h"
#include "../production_control/NotificationTypes.h"
#include "../../src/production_control/states_controller/SimulationWaitForConnectionsState.h"
#include "../test_helpers/MockObserver.h"
#include "../../src/production_control/SimulationConnectionHandler.h"

// Testen van events naar states (set state, add event, run, check new state)
BOOST_AUTO_TEST_SUITE(ProductionControlTestControllerEventProcesses)

BOOST_AUTO_TEST_CASE(ProductionControlTestControllerEventMachineRegistered) {
  auto machineNetwork = std::make_shared<testutils::MockNetwork>();
  simulation::SimulationController controller;

  BOOST_CHECK_NO_THROW(controller.setConfigFromFile("./test_configs/test_config_one_machine.yaml"));

  // Machine 1 should be loaded
  BOOST_CHECK_EQUAL(!!controller.getMachine(1), true);

  // Setting this state will setup the server
  auto state = states::SimulationWaitForConnectionsState(controller);
  controller.setCurrentState(std::make_shared<states::SimulationWaitForConnectionsState>(state));

  BOOST_CHECK_EQUAL(controller.getMachine(1)->isSimulationConnected(), false);

  // Connect a machine
  machineNetwork->startMockMCClientController();

  patterns::NotifyObserver::NotifyEvent e(NotifyEventIds::eControllerRegisterMachine);
  e.setArgument(0, (uint16_t) 1);
  e.setArgument(1, machineNetwork->getConnection());

  // Notify controller of new event, creates new state event
  BOOST_CHECK_NO_THROW(controller.handleNotification(e));

  // Run context to handle the state event
  BOOST_CHECK_NO_THROW(controller.run());

  BOOST_CHECK_EQUAL(controller.getMachine(1)->isSimulationConnected(), true);


  machineNetwork->stop();
  controller.stop();

}

BOOST_AUTO_TEST_CASE(ProductionControlTest2) {

  BOOST_REQUIRE_EQUAL(1, 1);

}
// Einde state tests
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ProductionControlSimulationNetwork)

BOOST_AUTO_TEST_CASE(RegisterSimulationMachine)
{
  testUtils::NotificationHandlerFn fn = [](const patterns::NotifyObserver::NotifyEvent &notification){
    std::cout << "========Running checks!==========" << std::endl;
    BOOST_CHECK(notification.getEventId() == NotifyEventIds::SimulationNotificationTypes::eSimRegisterMachine);
    BOOST_CHECK(notification.getArgumentAsType<uint16_t >(0) == 1);
    BOOST_CHECK(notification.getArgumentAsType<Network::ConnectionPtr>(1) != nullptr);
  };

  testUtils::MockObserver observer;
  observer.setHandleNotificationFn(fn);

  Network::Manager serverManager;
  serverManager.setLocalPort(Network::Protocol::PORT_SIMULATION_COMMUNICATION);

  simulation::SimulationConnectionHandler handler;

  handler.addObserver(observer);

  auto serverThread = serverManager.runServiceThread();
  auto server = serverManager.createServer(std::make_shared<simulation::SimulationConnectionHandler>(handler), 10);

  server->start();
  auto clientMock = std::make_shared<testutils::MockNetwork>();
  clientMock->startMockMCClientController();

  Network::Message msg;

  msg.setMessageType(Network::Protocol::SimMessageType::kSimMessageTypeRegister);
  msg.setBody("1");

  clientMock->sendMessage(msg);

  sleep(1);

  serverManager.stop();
  serverThread->join();
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ProductionControlTestControllerPublicMethods)

BOOST_AUTO_TEST_CASE(ProductionControlTestControllerLoadConfig) {
  simulation::SimulationController controller;
  BOOST_REQUIRE_NO_THROW(controller.setConfigFromFile("../tests/production_control/testconfig.yaml"));
  auto machine1 = controller.getMachine(15);
  auto machine2 = controller.getMachine(75);

  BOOST_REQUIRE(machine1);
  BOOST_REQUIRE(machine2);

  BOOST_CHECK(machine1->getName() == "Testmachine15");
  BOOST_CHECK(machine2->getName() == "Testmachine75");

  auto m1config = machine1->getConfigurations()[0];
  auto m2config = machine2->getConfigurations()[0];

  BOOST_CHECK(m1config.getNextMachineId() == 75);
  BOOST_CHECK(m1config.getInitializationDurationInSeconds() == 6);
  BOOST_CHECK(m1config.getInputBufferSize() == 68);
  BOOST_CHECK(m1config.getInputMaterialsForEachProduct() == 1);
  BOOST_CHECK(m1config.getMeanTimeBetweenFailureInHours()== 8800);
  BOOST_CHECK(m1config.getMeanTimeBetweenFailureStddevInHours() == 30);
  BOOST_CHECK(m1config.getOutputEachMinute() == 12);
  BOOST_CHECK(m1config.getReparationTimeInMinutes() == 24);
  BOOST_CHECK(m1config.getProductId() == 12);

  BOOST_CHECK(m2config.getNextMachineId() == 0);
  BOOST_CHECK(m2config.getInitializationDurationInSeconds() == 7);
  BOOST_CHECK(m2config.getInputBufferSize() == 69);
  BOOST_CHECK(m2config.getInputMaterialsForEachProduct() == 2);
  BOOST_CHECK(m2config.getMeanTimeBetweenFailureInHours()== 8801);
  BOOST_CHECK(m2config.getMeanTimeBetweenFailureStddevInHours() == 31);
  BOOST_CHECK(m2config.getOutputEachMinute() == 13);
  BOOST_CHECK(m2config.getReparationTimeInMinutes() == 25);
  BOOST_CHECK(m2config.getProductId() == 88);

  m1config = machine1->getConfigurations()[1];
  m2config = machine2->getConfigurations()[1];

  BOOST_CHECK(m1config.getNextMachineId() == 2);
  BOOST_CHECK(m1config.getInitializationDurationInSeconds() == 9);
  BOOST_CHECK(m1config.getInputBufferSize() == 68);
  BOOST_CHECK(m1config.getInputMaterialsForEachProduct() == 3);
  BOOST_CHECK(m1config.getMeanTimeBetweenFailureInHours()== 9800);
  BOOST_CHECK(m1config.getMeanTimeBetweenFailureStddevInHours() == 36);
  BOOST_CHECK(m1config.getOutputEachMinute() == 8);
  BOOST_CHECK(m1config.getReparationTimeInMinutes() == 27);
  BOOST_CHECK(m1config.getProductId() == 12);

  BOOST_CHECK(m2config.getNextMachineId() == 0);
  BOOST_CHECK(m2config.getInitializationDurationInSeconds() == 10);
  BOOST_CHECK(m2config.getInputBufferSize() == 69);
  BOOST_CHECK(m2config.getInputMaterialsForEachProduct() == 4);
  BOOST_CHECK(m2config.getMeanTimeBetweenFailureInHours()== 9801);
  BOOST_CHECK(m2config.getMeanTimeBetweenFailureStddevInHours() == 37);
  BOOST_CHECK(m2config.getOutputEachMinute() == 9);
  BOOST_CHECK(m2config.getReparationTimeInMinutes() == 28);
  BOOST_CHECK(m2config.getProductId() == 88);
}

// Einde public method tests
BOOST_AUTO_TEST_SUITE_END()
