/*
 * Test Production Control - Controller
 */


// http://www.boost.org/doc/libs/1_60_0/libs/test/doc/html/boost_test/adv_scenarios/shared_lib_customizations/entry_point.html

#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <network/Client.h>

#include <patterns/notifyobserver/Notifier.hpp>

#include "../test_helpers/MockNetwork.h"
#include "../production_control/SimulationController.h"
#include "../production_control/NotificationTypes.h"
#include "../../src/production_control/states_controller/SimulationWaitForConnectionsState.h"
#include "../../src/production_control/states_controller/OperationState.h"

// Testen van events naar states (set state, add event, run, check new state)
BOOST_AUTO_TEST_SUITE(ProductionControlTestControllerEventProcesses)

BOOST_AUTO_TEST_CASE(ProductionControlTestControllerEventMachineRegistered) {
  auto machineNetwork = std::make_shared<testUtils::MockNetwork>();
  Simulation::SimulationController controller;

  controller.setConfigFromFile("test_configs/test_config_one_machine.yaml");

  // Machine 1 should be loaded
  BOOST_CHECK(!!controller.getMachine(1));

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

  BOOST_CHECK(controller.getMachine(1)->isSimulationConnected());

  BOOST_CHECK(controller.allMachinesConnected());

  BOOST_CHECK_NO_THROW(controller.run());

  auto newState = controller.getCurrentState();

  BOOST_CHECK(!!std::dynamic_pointer_cast<States::OperationState>(newState));

  machineNetwork->stop();
  controller.stop();

}

BOOST_AUTO_TEST_CASE(ProductionControlTest2) {

  BOOST_REQUIRE_EQUAL(1, 1);

}
// Einde state tests
BOOST_AUTO_TEST_SUITE_END()

// Testen van public methods van controller
BOOST_AUTO_TEST_SUITE(ProductionControlTestControllerPublicMethods)

BOOST_AUTO_TEST_CASE(ProductionControlTestControllerLoadConfig) {
  Simulation::SimulationController controller;
  // TODO: test config file toevoegen aan build (dat na compile naast de executable staat)
  controller.setConfigFromFile("../../configs/configfile.yaml");
}

BOOST_AUTO_TEST_CASE(ProductionControlTest2) {

  BOOST_REQUIRE_EQUAL(2, 2);

}
// Einde public method tests
BOOST_AUTO_TEST_SUITE_END()
