
#define BOOST_TEST_DYN_LINK

#include <vector>

#include <boost/test/unit_test.hpp>

#include "../test_helpers/MockNetwork.h"
#include "../test_helpers/HelperFunctions.h"

#include "../machine_control/SimulationController.h"
#include "../../src/machine_control/states_simulation_controller/FindProductControlState.h"
#include "../../src/machine_control/states_simulation_controller/ConnectSimulationState.h"
#include "../../src/machine_control/states_simulation_controller/InitializeSimulationState.h"
#include "../../src/machine_control/states_simulation_controller/OffState.h"
#include "../../src/machine_control/states_simulation_controller/OnState.h"

BOOST_AUTO_TEST_SUITE(MachineControlTestControllerStates)

BOOST_AUTO_TEST_CASE(MachineControlTestControllerFindProductControlState) {
  // set the SimulationController with a machine id of 1
  simulator::SimulationController controller(1);

  // set the FindProductControlState state
  auto findProductionControlState = std::make_shared<simulationstates::FindProductControlState>(controller);
  BOOST_CHECK_NO_THROW(controller.setCurrentState(findProductionControlState));

  // run the controller
  BOOST_CHECK_NO_THROW(controller.run());

  // check if the state has changed to the next state
  auto currentState = controller.getCurrentState();
  bool isState = !!std::dynamic_pointer_cast<simulationstates::ConnectSimulationState>(currentState);
  BOOST_REQUIRE_EQUAL(isState, true);

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

  controller.setupNetwork();
  productionControlServer->awaitClientConnecting(1000);

  BOOST_REQUIRE_NO_THROW(controller.setCurrentState(std::make_shared<simulationstates::InitializeSimulationState>(controller)));

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
  auto productionControl = std::make_shared<testutils::MockNetwork>();
  productionControl->startMockPCServerApplication();

  BOOST_REQUIRE_NO_THROW(controller.setCurrentState(std::make_shared<simulationstates::OnState>(controller)));

  productionControl->awaitClientConnecting();

  auto event = std::make_shared<patterns::statemachine::Event>(simulationstates::kEventTypePowerOff);
  BOOST_REQUIRE_NO_THROW(controller.scheduleEvent(event));

  BOOST_REQUIRE_NO_THROW(controller.run());

  BOOST_REQUIRE_EQUAL(!!std::dynamic_pointer_cast<simulationstates::OffState>(controller.getCurrentState()), true);

  productionControl->stop();
}

// Einde public method tests
BOOST_AUTO_TEST_SUITE_END()