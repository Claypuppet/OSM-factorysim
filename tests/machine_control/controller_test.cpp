//
// Created by hqnders on 09/05/18.
//
#define BOOST_TEST_DYN_LINK

#include <vector>

#include <boost/test/unit_test.hpp>

#include "../test_helpers/MockNetwork.h"
#include "../test_helpers/HelperFunctions.h"

#include "../../src/libs/network/Protocol.h"
#include "../../src/libs/network/Message.h"

#include "../machine_control/SimulationController.h"
#include "../../src/machine_control/states_simulation/FindProductControlState.h"
#include "../../src/machine_control/states_simulation/ConnectSimulationState.h"
#include "../../src/machine_control/states_simulation/InitializeSimulationState.h"
#include "../../src/machine_control/states_simulation/OffState.h"
#include "../../src/machine_control/states_simulation/OnState.h"
#include "../../src/machine_control/states_simulation/SimulationState.h"



BOOST_AUTO_TEST_SUITE(MachineControlTestControllerStates)

BOOST_AUTO_TEST_CASE(MachineControlTestControllerFindProductControlState) {
  simulator::SimulationController controller(1);

  BOOST_CHECK_NO_THROW(controller.setCurrentState(std::make_shared<simulationstates::FindProductControlState>(controller)));

  BOOST_CHECK_NO_THROW(controller.run());

  BOOST_REQUIRE_EQUAL(!!std::dynamic_pointer_cast<simulationstates::ConnectSimulationState>(controller.getCurrentState()), true);

  controller.stop();
}

BOOST_AUTO_TEST_CASE(MachineControlTestControllerConnectSimulationState){
  auto productionControl = std::make_shared<testutils::MockNetwork>();

  productionControl->startMockPCServerController();

  simulator::SimulationController controller(1);

  BOOST_REQUIRE_NO_THROW(controller.setCurrentState(std::make_shared<simulationstates::ConnectSimulationState>(controller)));

  productionControl->awaitClientConnecting(1000);

  auto event = std::make_shared<patterns::statemachine::Event>(simulationstates::kEventTypeConnected);
  BOOST_REQUIRE_NO_THROW(controller.scheduleEvent(event));

  BOOST_REQUIRE_NO_THROW(controller.run());

  BOOST_REQUIRE_EQUAL(!!std::dynamic_pointer_cast<simulationstates::InitializeSimulationState>(controller.getCurrentState()), true);

  controller.stop();
  productionControl->stop();
}

BOOST_AUTO_TEST_CASE(MachineControlTestControllerInitializeSimulationState){
  auto productionControlServer = std::make_shared<testutils::MockNetwork>();
  
  productionControlServer->startMockPCServerController();
  
  simulator::SimulationController controller(1);

  BOOST_REQUIRE_NO_THROW(controller.setCurrentState(std::make_shared<simulationstates::InitializeSimulationState>(controller)));

  productionControlServer->awaitClientConnecting(1000);

  auto event = std::make_shared<patterns::statemachine::Event>(simulationstates::kEventTypeSimulationConfigurationsReceived);
  std::vector<models::MachineConfiguration> argument;
  BOOST_REQUIRE_NO_THROW(event->setArgument(argument));

  BOOST_REQUIRE_NO_THROW(controller.scheduleEvent(event));

  BOOST_REQUIRE_NO_THROW(controller.run());

  BOOST_REQUIRE_EQUAL(!!std::dynamic_pointer_cast<simulationstates::OffState>(controller.getCurrentState()), true);

  controller.stop();
  productionControlServer->stop();
}

BOOST_AUTO_TEST_CASE(MachineControlTestControllerOffState) {
  simulator::SimulationController controller(1);

  BOOST_REQUIRE_NO_THROW(controller.setCurrentState(std::make_shared<simulationstates::OffState>(controller)));

  auto event = std::make_shared<patterns::statemachine::Event>(simulationstates::kEventTypePowerOn);
  BOOST_REQUIRE_NO_THROW(controller.scheduleEvent(event));

  BOOST_REQUIRE_NO_THROW(controller.run());

  BOOST_REQUIRE_EQUAL(!!std::dynamic_pointer_cast<simulationstates::OnState>(controller.getCurrentState()), true);
}

BOOST_AUTO_TEST_CASE(MachineControlTestControllerOnState) {
  simulator::SimulationController controller(1);

  BOOST_REQUIRE_NO_THROW(controller.setCurrentState(std::make_shared<simulationstates::OnState>(controller)));

  auto event = std::make_shared<patterns::statemachine::Event>(simulationstates::kEventTypePowerOff);
  BOOST_REQUIRE_NO_THROW(controller.scheduleEvent(event));

  BOOST_REQUIRE_NO_THROW(controller.run());

  BOOST_REQUIRE_EQUAL(!!std::dynamic_pointer_cast<simulationstates::OffState>(controller.getCurrentState()), true);
}

// Einde public method tests
BOOST_AUTO_TEST_SUITE_END()