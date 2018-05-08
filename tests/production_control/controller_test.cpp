/*
 * Test Production Control - Controller
 */

#include <patterns/notifyobserver/Notifier.hpp>

#include "../production_control/SimulationController.h"
#include "../production_control/NotificationTypes.h"
#include "../../src/production_control/states_controller/SimulationWaitForConnectionsState.h"

// http://www.boost.org/doc/libs/1_60_0/libs/test/doc/html/boost_test/adv_scenarios/shared_lib_customizations/entry_point.html

#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <network/Client.h>

// Testen van events naar states (set state, add event, run, check new state)
BOOST_AUTO_TEST_SUITE(ProductionControlTestControllerEventProcesses)

BOOST_AUTO_TEST_CASE(ProductionControlTestControllerEventMachineRegistered) {
  Simulation::SimulationController controller;
  auto state = States::SimulationWaitForConnectionsState(controller);
  controller.setCurrentState(std::make_shared<States::SimulationWaitForConnectionsState>(state));
  Patterns::NotifyObserver::NotifyEvent e(NotifyEventIds::eControllerRegisterMachine);
  e.setArgument(0, (uint16_t) 1);

  // TODO: get real connection, else boost throws error because its currently a nullptr
  e.setArgument(1, std::shared_ptr<Network::ConnectionPtr>());

  // Notify controller of new event, creates new state event
  BOOST_CHECK_NO_THROW(controller.handleNotification(e));

  // Run context to handle the state event
  BOOST_CHECK_NO_THROW(controller.run());

  // TODO: check current state

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
  controller.setConfigFromFile("../tests/production_control/testconfig.yaml");
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

BOOST_AUTO_TEST_CASE(ProductionControlTest2) {

  BOOST_REQUIRE_EQUAL(2, 2);

}
// Einde public method tests
BOOST_AUTO_TEST_SUITE_END()
