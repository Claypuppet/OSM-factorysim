//
// Created by hqnders on 09/05/18.
//
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

#include "../test_helpers/MockNetwork.h"
#include "../test_helpers/HelperFunctions.h"

#include "../machine_control/SimulationController.h"
#include "../../src/machine_control/states_simulation/FindProductControlState.h"
#include "../../src/machine_control/states_simulation/ConnectSimulationState.h"
#include "../../src/machine_control/states_simulation/InitializeSimulationState.h"

BOOST_AUTO_TEST_SUITE(MachineControlTestControllerStates)

BOOST_AUTO_TEST_CASE(MachineControlTestControllerFindProductControlState) {
  auto machineNetwork = std::make_shared<testutils::MockNetwork>();

  simulator::SimulationController controller(1);

  BOOST_CHECK_NO_THROW(controller.setCurrentState(std::make_shared<simulationstates::FindProductControlState>(controller)));

  BOOST_CHECK_NO_THROW(controller.run());

  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<simulationstates::ConnectSimulationState>(controller.getCurrentState()), true);

  controller.stop();
  machineNetwork->stop();
}

BOOST_AUTO_TEST_CASE(MachineControlTestControllerConnectSimulationState){
  auto productionControlServer = std::make_shared<testutils::MockNetwork>();

  productionControlServer->startMockPCServerController();

  simulator::SimulationController controller(1);

  BOOST_CHECK_NO_THROW(controller.setCurrentState(std::make_shared<simulationstates::ConnectSimulationState>(controller)));

  productionControlServer->awaitClientConnecting(1000);



  BOOST_CHECK_NO_THROW(controller.run());

  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<simulationstates::InitializeSimulationState>(controller.getCurrentState()), true);

  controller.stop();
  productionControlServer->stop();

}

// Einde public method tests
BOOST_AUTO_TEST_SUITE_END()