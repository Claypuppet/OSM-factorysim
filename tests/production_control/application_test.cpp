//
// Created by bas on 15-5-18.
//

#define BOOST_TEST_DYN_LINK

#include <memory>

#include <boost/test/unit_test.hpp>
#include <patterns/notifyobserver/Notifier.hpp>

#include "../test_helpers/MockNetwork.h"
#include "../../src/production_control/states_application/WaitForConnectionsState.h"
#include "../../src/production_control/SimulationController.h"
#include "../../src/production_control/NotificationTypes.h"

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
