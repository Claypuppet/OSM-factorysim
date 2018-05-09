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
  auto machineNetwork = std::make_shared<testUtils::MockNetwork>();
  Simulation::SimulationController controller;

  BOOST_CHECK_NO_THROW(controller.setConfigFromFile("./test_configs/test_config_one_machine.yaml"));

  // Machine 1 should be loaded
  BOOST_CHECK_EQUAL(!!controller.getMachine(1), true);

  // Setting this state will setup the server
  auto state = States::SimulationWaitForConnectionsState(controller);
  controller.setCurrentState(std::make_shared<States::SimulationWaitForConnectionsState>(state));

  BOOST_CHECK_EQUAL(controller.getMachine(1)->isSimulationConnected(), false);

  // Connect a machine
  machineNetwork->startMockMCClientController();

  Patterns::NotifyObserver::NotifyEvent e(NotifyEventIds::eControllerRegisterMachine);
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
  testUtils::NotificationHandlerFn fn = [](const Patterns::NotifyObserver::NotifyEvent &notification){
    std::cout << "========Running checks!==========" << std::endl;
    BOOST_CHECK(notification.getEventId() == NotifyEventIds::SimulationNotificationTypes::eSimRegisterMachine);
    BOOST_CHECK(notification.getArgumentAsType<uint16_t >(0) == 1);
    BOOST_CHECK(notification.getArgumentAsType<Network::ConnectionPtr>(1) != nullptr);
  };

  testUtils::MockObserver observer;
  observer.setHandleNotificationFn(fn);

  Network::Manager serverManager;
  serverManager.setLocalPort(Network::Protocol::kPortSimulationCommunication);

  Simulation::SimulationConnectionHandler handler;

  handler.addObserver(observer);

  auto serverThread = serverManager.runServiceThread();
  auto server = serverManager.createServer(std::make_shared<Simulation::SimulationConnectionHandler>(handler), 10);

  server->start();
  auto clientMock = std::make_shared<testUtils::MockNetwork>();
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

// Testen van public methods van controller
BOOST_AUTO_TEST_SUITE(ProductionControlTestControllerPublicMethods)

BOOST_AUTO_TEST_CASE(ProductionControlTestControllerLoadConfig) {
  Simulation::SimulationController controller;
  // TODO: test config file toevoegen aan build (dat na compile naast de executable staat)
  //controller.setConfigFromFile("../../configs/configfile.yaml");
}

BOOST_AUTO_TEST_CASE(ProductionControlTest2) {

  BOOST_REQUIRE_EQUAL(2, 2);

}
// Einde public method tests
BOOST_AUTO_TEST_SUITE_END()
