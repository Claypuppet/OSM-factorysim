//
// Created by hqnders on 09/05/18.
//
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

#include "../test_helpers/MockNetwork.h"

#include "../machine_control/SimulationController.h"
#include "../../src/machine_control/states_simulation/FindProductControlState.h"
#include "../../src/machine_control/states_simulation/ConnectSimulationState.h"

BOOST_AUTO_TEST_SUITE(MachineControlTestControllerStates)

BOOST_AUTO_TEST_CASE(MachineControlTestControllerFindProductControlState) {
  auto machineNetwork = std::make_shared<testUtils::MockNetwork>();

  models::Machine machine;
  simulator::SimulationController controller(machine);

  BOOST_CHECK_NO_THROW(controller.setCurrentState(std::make_shared<simulationstates::FindProductControlState>(controller)));

  BOOST_CHECK_NO_THROW(controller.run());

  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<simulationstates::ConnectSimulationState>(controller.getCurrentState()), true);

  controller.stop();
  machineNetwork->stop();
}

// Einde public method tests
BOOST_AUTO_TEST_SUITE_END()