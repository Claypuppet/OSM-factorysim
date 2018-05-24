/*
 * Test Production Control - Controller
 */


// http://www.boost.org/doc/libs/1_60_0/libs/test/doc/html/boost_test/adv_scenarios/shared_lib_customizations/entry_point.html

#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

#include <network/Client.h>
#include <patterns/notifyobserver/Notifier.hpp>

#include "../test_helpers/MockNetwork.h"

#include "../../src/production_control/SimulationController.h"
#include "../../src/production_control/NotificationTypes.h"
#include "../../src/production_control/states_controller/SimulationWaitForConnectionsState.h"
#include "../../src/production_control/states_controller/LoadConfigState.h"
#include "../../src/production_control/states_controller/SimulationBroadcastState.h"
#include "../../src/production_control/states_controller/OperationState.h"

// Testen van events naar states (set state, add event, run, check new state)
BOOST_AUTO_TEST_SUITE(ProductionControlTestControllerEventProcesses)

BOOST_AUTO_TEST_CASE(ProductionControlTestControllerEventMachineRegistered) {
  auto machineNetwork = std::make_shared<testutils::MockNetwork>();
  simulation::SimulationController controller;

  BOOST_CHECK_NO_THROW(controller.setConfigFromFile("./test_configs/test_config_one_machine.yaml"));

  // Machine 1 should be loaded
  auto machine = controller.getSimulationMachine(1);
  BOOST_REQUIRE(machine);

  // Setting this state will setup the server
  auto state = states::SimulationWaitForConnectionsState(controller);
  BOOST_CHECK_NO_THROW(controller.setCurrentState(std::make_shared<states::SimulationWaitForConnectionsState>(state)));

  BOOST_CHECK_EQUAL(machine->isSimulationConnected(), false);

  // Connect a machine
  machineNetwork->startMockMCClientController();

  patterns::notifyobserver::NotifyEvent event(NotifyEventIds::eSimRegisterMachine);
  event.setArgument(0, (uint16_t) 1);
  event.setArgument(1, machineNetwork->getConnection());

  // Notify controller of new event, creates new state event
  BOOST_CHECK_NO_THROW(controller.handleNotification(event));

  // Run context to handle the state event
  BOOST_CHECK_NO_THROW(controller.run());

  BOOST_CHECK(controller.getSimulationMachine(1)->isSimulationConnected());

  // set machine ready, to "mock" that he received config
  BOOST_CHECK_NO_THROW(controller.machineReady(1));

  BOOST_CHECK(controller.allMachinesReady());

  BOOST_CHECK_NO_THROW(controller.run());

  // Get current state and check if we are in the next
  auto currentState = controller.getCurrentState();
  BOOST_CHECK(!!std::dynamic_pointer_cast<states::OperationState>(currentState));

  machineNetwork->stop();
  controller.stop();
}

// Einde state tests
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ProductionControlControllerStates)

BOOST_AUTO_TEST_CASE(ProductionControlLoadConfigurationState)
{
  simulation::SimulationController controller;
  //Set load config state
  BOOST_REQUIRE_NO_THROW(controller.setCurrentState(std::make_shared<states::LoadConfigState>(controller)));

  //Schedule load config event
  patterns::statemachine::EventPtr event = std::make_shared<states::Event>(states::kEventTypeReadConfigFile);
  event->setArgument<std::string>("./test_configs/test_config_one_machine.json");
  BOOST_REQUIRE_NO_THROW(controller.scheduleEvent(event));

  //Run the state
  BOOST_REQUIRE_NO_THROW(controller.run());

  //Loadconfig state should go to the SimulationBroadcastState but that state instantly switches to SimulationWaitForConnectionsState
  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<states::SimulationWaitForConnectionsState>(controller.getCurrentState()), true);
  controller.stop();
}

BOOST_AUTO_TEST_SUITE_END()

// Testen van public methods van controllerAdded test case and test_config_two_machines.yaml
BOOST_AUTO_TEST_SUITE(ProductionControlTestControllerPublicMethods)

BOOST_AUTO_TEST_CASE(ProductionControlTestControllerLoadConfig) {
  simulation::SimulationController controller;
  BOOST_REQUIRE_NO_THROW(controller.setConfigFromFile("./test_configs/test_config_two_machines.json"));

  controller.printMachinesLength();

  auto machine1 = controller.getSimulationMachine(15);
  auto machine2 = controller.getSimulationMachine(75);

  BOOST_REQUIRE(machine1);
  BOOST_REQUIRE(machine2);

  BOOST_CHECK(machine1->getName() == "Testmachine15");
  BOOST_CHECK(machine2->getName() == "Testmachine75");

  auto m1config = machine1->getConfigurations()[0];
  auto m2config = machine2->getConfigurations()[0];

//  auto m1previousMachines = m1config.getPreviousMachines(); // has no previous machines
  auto m2PreviousMachines = m2config.getPreviousMachines();

  // check m1 configuration settings
  BOOST_CHECK(m1config.getInitializationDurationInSeconds() == 6);
  BOOST_CHECK(m1config.getOutputBufferSize() == 14);
  BOOST_CHECK(m1config.getMeanTimeBetweenFailureInHours()== 8800);
  BOOST_CHECK(m1config.getMeanTimeBetweenFailureStddevInHours() == 30);
  BOOST_CHECK(m1config.getOutputEachMinute() == 12);
  BOOST_CHECK(m1config.getReparationTimeInMinutes() == 24);
  BOOST_CHECK(m1config.getProductId() == 12);
  BOOST_CHECK(m1config.getOutputBufferSize() == 14);

  // check m1 previousmachine configuration settings
  // machine 1 has no previous machines, so nothing to test there...

  BOOST_REQUIRE_EQUAL(m2PreviousMachines.size(), 1);

  auto m2PreviousMachine1 = m2PreviousMachines[0];

  BOOST_CHECK_EQUAL(m2PreviousMachine1.getMachineId(), 15);
  BOOST_CHECK_EQUAL(m2PreviousMachine1.getNeededProducts(), 7);

  // check m1 configuration settings
  BOOST_CHECK(m2config.getInitializationDurationInSeconds() == 7);
  BOOST_CHECK(m2config.getOutputBufferSize() == 43);
  BOOST_CHECK(m2config.getMeanTimeBetweenFailureInHours()== 8801);
  BOOST_CHECK(m2config.getMeanTimeBetweenFailureStddevInHours() == 31);
  BOOST_CHECK(m2config.getOutputEachMinute() == 13);
  BOOST_CHECK(m2config.getReparationTimeInMinutes() == 25);
  BOOST_CHECK(m2config.getProductId() == 12);
  BOOST_CHECK(m1config.getOutputBufferSize() == 43);

  // check m1 previousmachine configuration settings

  m1config = machine1->getConfigurations()[1];
  m2config = machine2->getConfigurations()[1];

  // m1config has no previous machines, so nothing to test there...
  m2PreviousMachines = m2config.getPreviousMachines();

  BOOST_CHECK(m1config.getInitializationDurationInSeconds() == 9);
  BOOST_CHECK(m1config.getOutputBufferSize() == 39);
  BOOST_CHECK(m1config.getMeanTimeBetweenFailureInHours()== 9800);
  BOOST_CHECK(m1config.getMeanTimeBetweenFailureStddevInHours() == 36);
  BOOST_CHECK(m1config.getOutputEachMinute() == 8);
  BOOST_CHECK(m1config.getReparationTimeInMinutes() == 27);
  BOOST_CHECK(m1config.getProductId() == 88);
  BOOST_CHECK(m1config.getOutputBufferSize() == 39);

  BOOST_CHECK(m2config.getInitializationDurationInSeconds() == 10);
  BOOST_CHECK(m2config.getOutputBufferSize() == 69);
  BOOST_CHECK(m2config.getMeanTimeBetweenFailureInHours()== 9801);
  BOOST_CHECK(m2config.getMeanTimeBetweenFailureStddevInHours() == 37);
  BOOST_CHECK(m2config.getOutputEachMinute() == 9);
  BOOST_CHECK(m2config.getReparationTimeInMinutes() == 28);
  BOOST_CHECK(m2config.getProductId() == 88);
  BOOST_CHECK(m1config.getOutputBufferSize() == 69);

  // check m1 previousmachine configuration settings
  // machine 1 has no previous machines, so nothing to test there...

  auto m2PreviousMachine2 = m2PreviousMachines[0];

  BOOST_CHECK_EQUAL(m2PreviousMachine2.getMachineId(), 15);
  BOOST_CHECK_EQUAL(m2PreviousMachine2.getNeededProducts(), 8);
}

// Einde public method tests
BOOST_AUTO_TEST_SUITE_END()

// Testen van public methods van controller
BOOST_AUTO_TEST_SUITE(ProductionControlTestControllerNetwork)

BOOST_AUTO_TEST_CASE(SendTurnOn) {
  // Create server and client
  auto machineEndpoint = std::make_shared<testutils::MockNetwork>();
  auto productionServer = std::make_shared<testutils::MockNetwork>();

  // Start server, start client, wait for connection on server
  productionServer->startMockPCServerController();
  machineEndpoint->startMockMCClientController();
  productionServer->awaitClientConnecting();

  // Create machine with connection (in production control)
  auto machine = simulation::SimulationMachine(1);
  machine.setSimulationConnection(productionServer->getConnection());

  // prepare test on machine control when message will receive
  testutils::OnMessageFn callback = [](network::Message &message){
    BOOST_CHECK_EQUAL(message.getMessageType(), network::Protocol::kSimMessageTypeTurnOn);
  };
  machineEndpoint->setOnMessageFn(callback);
  machine.sendTurnOnCommand();

  // wait for the message received
  machineEndpoint->awaitMessageReceived();

  machineEndpoint->stop();
  productionServer->stop();
}

BOOST_AUTO_TEST_CASE(SendTurnOff) {
  // Create server and client
  auto machineEndpoint = std::make_shared<testutils::MockNetwork>();
  auto productionServer = std::make_shared<testutils::MockNetwork>();

  // Start server, start client, wait for connection on server
  productionServer->startMockPCServerController();
  machineEndpoint->startMockMCClientController();
  productionServer->awaitClientConnecting();

  // Create machine with connection (in production control)
  auto machine = simulation::SimulationMachine(1);
  machine.setSimulationConnection(productionServer->getConnection());

  // prepare test on machine control when message will receive
  testutils::OnMessageFn callback = [](network::Message &message){
    BOOST_CHECK_EQUAL(message.getMessageType(), network::Protocol::kSimMessageTypeTurnOff);
  };
  machineEndpoint->setOnMessageFn(callback);
  machine.sendTurnOffCommand();

  // wait for the message received
  machineEndpoint->awaitMessageReceived();

  machineEndpoint->stop();
  productionServer->stop();
}

// TODO !!! Move this to application_test after Bas has committed & merged it with dev
BOOST_AUTO_TEST_CASE(SendTurnReconfigure) {
  // Create server and client
  auto machineEndpoint = std::make_shared<testutils::MockNetwork>();
  auto productionServer = std::make_shared<testutils::MockNetwork>();

  // Start server, start client, wait for connection on server
  productionServer->startMockPCServerApplication();
  machineEndpoint->startMockMCClientApplication();
  productionServer->awaitClientConnecting();

  // Create machine with connection (in production control)
  auto machine = core::Machine(1);
  machine.setConnection(productionServer->getConnection());

  // prepare test on machine control when message will receive
  testutils::OnMessageFn callback = [](network::Message &message){
    BOOST_CHECK_EQUAL(message.getMessageType(), network::Protocol::kAppMessageTypeReconfigure);
    BOOST_CHECK_EQUAL(message.getBodyObject<uint16_t>(), 1);
  };
  machineEndpoint->setOnMessageFn(callback);
  machine.sendConfigureMessage(1);

  // wait for the message received
  machineEndpoint->awaitMessageReceived();

  machineEndpoint->stop();
  productionServer->stop();
}

BOOST_AUTO_TEST_CASE(ProductionControlTest2) {

  BOOST_REQUIRE_EQUAL(2, 2);

}
// Einde public method tests
BOOST_AUTO_TEST_SUITE_END()
