/*
 * Test Production Control - Controller
 */


// http://www.boost.org/doc/libs/1_60_0/libs/test/doc/html/boost_test/adv_scenarios/shared_lib_customizations/entry_point.html

#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

#include <network/Client.h>
#include <patterns/notifyobserver/Notifier.hpp>
#include <yaml-cpp/exceptions.h>
#include <utils/time/Time.h>

#include "../test_helpers/MockNetwork.h"

#include "../../src/production_control/SimulationController.h"
#include "../../src/production_control/NotificationTypes.h"
#include "../../src/production_control/states_controller/SimulationWaitForConnectionsState.h"
#include "../../src/production_control/states_controller/LoadConfigState.h"
#include "../../src/production_control/states_controller/SimulationBroadcastState.h"
#include "../../src/production_control/states_controller/OperationState.h"
#include "../../src/production_control/states_controller/FinishedOperationState.h"
#include "../../src/production_control/states_controller/ControllerState.h"

const uint16_t machine1Id = 15;
const uint16_t machine2Id = 75;

// Testen van events naar states (set state, add event, run, check new state)
BOOST_AUTO_TEST_SUITE(ProductionControlTestControllerEventProcesses)

BOOST_AUTO_TEST_CASE(ProductionControlTestControllerEventSimulationFinsihedWithEvent) {
  simulation::SimulationController controller;

  BOOST_CHECK_NO_THROW(controller.setConfiguration("./test_configs/test_config_two_machines.yaml"));

  controller.setCurrentState(std::make_shared<states::OperationState>(controller));

  auto event = std::make_shared<states::Event>(states::kEventTypeSimulationFinished);
  controller.scheduleEvent(event);

  controller.run();

  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<states::FinishedOperationState>(controller.getCurrentState()), true);
}

BOOST_AUTO_TEST_CASE(ProductionControlTestControllerEventSimulationFinsihedWithTime) {
  simulation::SimulationController controller;
  utils::Time::getInstance().setType(utils::customTime);

  BOOST_CHECK_NO_THROW(controller.setConfiguration("./test_configs/test_config_two_machines.yaml"));

  controller.setCurrentState(std::make_shared<states::OperationState>(controller));

  uint64_t totalSimulationTime = (uint64_t)8760 * 60 * 60 * 1000; // total simulation time
  uint64_t simulationNotOverTime = totalSimulationTime - 10; // get timestamp just under the total time
  utils::Time::getInstance().syncTime(simulationNotOverTime); // set this time
  controller.run();
  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<states::OperationState>(controller.getCurrentState()), true);

  uint64_t millisToLetSimulationGetOverTime = 20;
  utils::Time::getInstance().increaseCurrentTime(millisToLetSimulationGetOverTime);
  controller.run();
  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<states::FinishedOperationState>(controller.getCurrentState()), true);
}

BOOST_AUTO_TEST_CASE(ProductionControlTestControllerEventMachineRegistered) {
  auto machineNetwork = std::make_shared<testutils::MockNetwork>();

  simulation::SimulationController controller;

  BOOST_CHECK_NO_THROW(controller.setConfiguration("./test_configs/test_config_one_machine.yaml"));

  // Machine 1 should be loaded
  auto machine = controller.getSimulationMachine(machine1Id);

  BOOST_REQUIRE(machine);

  // Setting this state will setup the server
  auto state = states::SimulationWaitForConnectionsState(controller);
  BOOST_CHECK_NO_THROW(controller.setCurrentState(std::make_shared<states::SimulationWaitForConnectionsState>(state)));

  BOOST_CHECK_EQUAL(machine->isSimulationConnected(), false);

  // Connect a machine
  machineNetwork->startMockMCClientController();

  patterns::notifyobserver::NotifyEvent event(NotifyEventIds::eSimRegisterMachine);
  event.setArgument(0, machine1Id);
  event.setArgument(1, machineNetwork->getConnection());

  // Notify controller of new event, creates new state event
  BOOST_CHECK_NO_THROW(controller.handleNotification(event));

  // Run context to handle the state event
  BOOST_CHECK_NO_THROW(controller.run());

  BOOST_CHECK(controller.getSimulationMachine(machine1Id)->isSimulationConnected());

  // set machine ready, to "mock" that he received config
  BOOST_CHECK_NO_THROW(controller.machineReady(machine1Id));

  BOOST_CHECK(controller.allMachinesReady());

  BOOST_CHECK_NO_THROW(controller.run());

  // Get current state and check if we are in the next
  auto currentState = controller.getCurrentState();
  BOOST_CHECK(!!std::dynamic_pointer_cast<states::OperationState>(currentState));

  controller.stop();
  machineNetwork->stop();
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
  event->setArgument<std::string>("./test_configs/test_config_two_machines.yaml");
  BOOST_REQUIRE_NO_THROW(controller.scheduleEvent(event));

  //Run the state
  BOOST_REQUIRE_NO_THROW(controller.run());
  //Loadconfig state should go to the SimulationBroadcastState
  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<states::SimulationBroadcastState>(controller.getCurrentState()), true);

  BOOST_REQUIRE_NO_THROW(controller.run());

  //Loadconfig state should go to the SimulationWaitForConnectionsState
  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<states::SimulationWaitForConnectionsState>(controller.getCurrentState()), true);
  controller.stop();
}

BOOST_AUTO_TEST_SUITE_END()

// Testen van public methods van controllerAdded test case and test_config_two_machines.yaml
BOOST_AUTO_TEST_SUITE(ProductionControlTestControllerPublicMethods)

BOOST_AUTO_TEST_CASE(ProductionControlTestControllerLoadConfigInvalidFileThrow) {
  simulation::SimulationController controller;
  const std::string configurationFilePath = "./invalid/file/path.yaml";
  BOOST_CHECK_THROW(controller.setConfiguration(configurationFilePath), YAML::Exception);
}

BOOST_AUTO_TEST_CASE(ProductionControlTestControllerLoadConfigIncompleteFileThrow) {
  simulation::SimulationController controller;
  const std::string configurationFilePath = "./test_configs/incomplete_configuration_file.yaml";
  BOOST_CHECK_THROW(controller.setConfiguration(configurationFilePath), YAML::Exception);
}

BOOST_AUTO_TEST_CASE(ProductionControlTestControllerLoadYAMLConfig) {
  simulation::SimulationController controller;
  const std::string configurationFilePath = "./test_configs/test_config_two_machines.yaml";
  BOOST_REQUIRE_NO_THROW(controller.setConfiguration(configurationFilePath));

  { // machine1
    uint16_t machineId = machine1Id;
    auto machine1 = controller.getSimulationMachine(machineId);
    BOOST_REQUIRE(machine1);

    BOOST_CHECK_EQUAL(machine1->getId(), machine1Id);
    BOOST_CHECK_EQUAL(machine1->getName(), "Testmachine15");
    BOOST_CHECK_EQUAL(machine1->getInitializationDurationInSeconds(), 6);
    BOOST_CHECK_EQUAL(machine1->getMeanTimeBetweenFailureInHours(), 8800);
    BOOST_CHECK_EQUAL(machine1->getReparationTimeInMinutes(), 24);
    BOOST_CHECK_EQUAL(machine1->getReparationTimeStddevInMinutes(), 30);

    auto machine1PostProcessInfo = machine1->getPostProcessInfo();
    BOOST_REQUIRE(machine1PostProcessInfo);

    auto machine1Configurations = machine1->getConfigurations();
    BOOST_REQUIRE_EQUAL(machine1Configurations.size(), 2);

    { // machine1 --> postProcessInfo
      BOOST_CHECK_EQUAL(machine1PostProcessInfo->getInputDelayInSeconds(), 20);
      BOOST_CHECK_EQUAL(machine1PostProcessInfo->getPostProcessDurationInMinutes(), 30);
    }

    { // machine1 --> machineConfiguration[0]
      auto machine1Configuration1 = machine1Configurations[0];

      BOOST_CHECK_EQUAL(machine1Configuration1->getProductId(), 12);
      BOOST_CHECK_EQUAL(machine1Configuration1->getOutputEachMinute(), 12);

      auto machine1Configuration1PreviousMachines = machine1Configuration1->getPreviousMachines();
      BOOST_REQUIRE_EQUAL(machine1Configuration1PreviousMachines.size(), 1);

      { // machine1 --> machineConfiguration[0] --> previousMachine[0]
        auto machine1Configuration1PreviousMachine1 = machine1Configuration1PreviousMachines[0];

        BOOST_CHECK_EQUAL(machine1Configuration1PreviousMachine1->getMachineId(), 0);
        BOOST_CHECK_EQUAL(machine1Configuration1PreviousMachine1->getNeededProducts(), 5);
        BOOST_CHECK_EQUAL(machine1Configuration1PreviousMachine1->getInputBufferSize(), 0);
      }
    }

    { // machine1 --> machineConfiguration[1]
      auto machine1Configuration2 = machine1Configurations[1];

      BOOST_CHECK(machine1Configuration2->getProductId() == 88);
      BOOST_CHECK(machine1Configuration2->getOutputEachMinute() == 8);

      auto machine1Configuration2PreviousMachines = machine1Configuration2->getPreviousMachines();
      BOOST_REQUIRE_EQUAL(machine1Configuration2PreviousMachines.size(), 1);

      { // machine1 --> machineConfiguration[1] --> previousMachine[0]
        auto machine1Configuration2PreviousMachine1 = machine1Configuration2PreviousMachines[0];

        BOOST_CHECK_EQUAL(machine1Configuration2PreviousMachine1->getMachineId(), 0);
        BOOST_CHECK_EQUAL(machine1Configuration2PreviousMachine1->getNeededProducts(), 10);
        BOOST_CHECK_EQUAL(machine1Configuration2PreviousMachine1->getInputBufferSize(), 0);
      }
    }
  }

  { // machine2
    auto machine2 = controller.getSimulationMachine(machine2Id);
    BOOST_REQUIRE(machine2);

    BOOST_CHECK(machine2->getId() == machine2Id);
    BOOST_CHECK(machine2->getName() == "Testmachine75");
    BOOST_CHECK(machine2->getInitializationDurationInSeconds() == 7);
    BOOST_CHECK(machine2->getMeanTimeBetweenFailureInHours()== 8801);
    BOOST_CHECK(machine2->getReparationTimeStddevInMinutes() == 31);
    BOOST_CHECK(machine2->getReparationTimeInMinutes() == 25);

    auto machine2PostProcessInfo = machine2->getPostProcessInfo();
    BOOST_REQUIRE(!machine2PostProcessInfo);

    auto machine2Configurations = machine2->getConfigurations();
    BOOST_REQUIRE(machine2Configurations.size() == 2);


    { // machine2 --> machineConfiguration[0]
      auto machine2Configuration1 = machine2Configurations[0];

      BOOST_CHECK(machine2Configuration1->getProductId() == 12);
      BOOST_CHECK(machine2Configuration1->getOutputEachMinute() == 8);

      auto machine2Configuration1PreviousMachines = machine2Configuration1->getPreviousMachines();
      BOOST_REQUIRE(machine2Configuration1PreviousMachines.size() == 1);

      { // machine2 --> machineConfiguration[0] --> previousMachine[0]
        auto machine2Configuration1PreviousMachine1 = machine2Configuration1PreviousMachines[0];

        BOOST_CHECK_EQUAL(machine2Configuration1PreviousMachine1->getMachineId(), machine1Id);
        BOOST_CHECK_EQUAL(machine2Configuration1PreviousMachine1->getNeededProducts(), 7);
        BOOST_CHECK_EQUAL(machine2Configuration1PreviousMachine1->getInputBufferSize(), 35);
      }
    }

    { // machine2 --> machineConfiguration[1]
      auto machine2Configuration2 = machine2Configurations[1];

      BOOST_CHECK(machine2Configuration2->getProductId() == 88);
      BOOST_CHECK(machine2Configuration2->getOutputEachMinute() == 8);

      auto machine2Configuration2PreviousMachines = machine2Configuration2->getPreviousMachines();
      BOOST_REQUIRE(machine2Configuration2PreviousMachines.size() == 1);

      { // machine2 --> machineConfiguration[1] --> previousMachine[0]
        auto machine2Configuration2PreviousMachine1 = machine2Configuration2PreviousMachines[0];

        BOOST_CHECK_EQUAL(machine2Configuration2PreviousMachine1->getMachineId(), machine1Id);
        BOOST_CHECK_EQUAL(machine2Configuration2PreviousMachine1->getNeededProducts(), 8);
        BOOST_CHECK_EQUAL(machine2Configuration2PreviousMachine1->getInputBufferSize(), 40);
      }
    }
  }
}

BOOST_AUTO_TEST_CASE(ProductionControlTestControllerLoadJSONConfig) {
  simulation::SimulationController controller;
  const std::string configurationFilePath = "./test_configs/test_config_two_machines.json";
  BOOST_REQUIRE_NO_THROW(controller.setConfiguration(configurationFilePath));

  { // machine1
    auto machine = controller.getSimulationMachine(machine1Id);
    BOOST_REQUIRE(machine);

    BOOST_CHECK(machine->getId() == machine1Id);
    BOOST_CHECK(machine->getName() == "Testmachine15");
    BOOST_CHECK(machine->getInitializationDurationInSeconds() == 6);
    BOOST_CHECK(machine->getMeanTimeBetweenFailureInHours()== 8800);
    BOOST_CHECK(machine->getReparationTimeStddevInMinutes() == 30);
    BOOST_CHECK(machine->getReparationTimeInMinutes() == 24);

    auto machinesConfigurations = machine->getConfigurations();
    BOOST_REQUIRE(machinesConfigurations.size() == 2);

    { // machine1 --> machineConfiguration[0]
      auto machineConfiguration = machinesConfigurations[0];

      BOOST_CHECK(machineConfiguration->getProductId() == 12);
      BOOST_CHECK(machineConfiguration->getOutputEachMinute() == 12);

      auto machine1Configuration1PreviousMachines = machineConfiguration->getPreviousMachines();
      BOOST_REQUIRE(machine1Configuration1PreviousMachines.size() == 1);

      { // machine1 --> machineConfiguration[0] --> previousMachine[0]
        auto previousMachine = machine1Configuration1PreviousMachines[0];

        BOOST_CHECK_EQUAL(previousMachine->getMachineId(), 0);
        BOOST_CHECK_EQUAL(previousMachine->getNeededProducts(), 5);
        BOOST_CHECK_EQUAL(previousMachine->getInputBufferSize(), 0);
      }
    }

    { // machine1 --> machineConfiguration[1]
      auto machineConfiguration = machinesConfigurations[1];

      BOOST_CHECK_EQUAL(machineConfiguration->getProductId(), 88);
      BOOST_CHECK_EQUAL(machineConfiguration->getOutputEachMinute(), 8);

      auto previousMachines = machineConfiguration->getPreviousMachines();
      BOOST_REQUIRE_EQUAL(previousMachines.size(), 1);

      { // machine1 --> machineConfiguration[1] --> previousMachine[0]
        auto previousMachine = previousMachines[0];

        BOOST_CHECK_EQUAL(previousMachine->getMachineId(), 0);
        BOOST_CHECK_EQUAL(previousMachine->getNeededProducts(), 10);
        BOOST_CHECK_EQUAL(previousMachine->getInputBufferSize(), 0);
      }
    }
  }

  { // machine2
    auto machine2 = controller.getSimulationMachine(machine2Id);
    BOOST_REQUIRE(machine2);

    BOOST_CHECK(machine2->getId() == machine2Id);
    BOOST_CHECK(machine2->getName() == "Testmachine75");
    BOOST_CHECK(machine2->getInitializationDurationInSeconds() == 7);
    BOOST_CHECK(machine2->getMeanTimeBetweenFailureInHours()== 8801);
    BOOST_CHECK(machine2->getReparationTimeStddevInMinutes() == 31);
    BOOST_CHECK(machine2->getReparationTimeInMinutes() == 25);

    auto machine2Configurations = machine2->getConfigurations();
    BOOST_REQUIRE(machine2Configurations.size() == 2);

    { // machine2 --> machineConfiguration[0]
      auto machine2Configuration1 = machine2Configurations[0];

      BOOST_CHECK_EQUAL(machine2Configuration1->getProductId(), 12);
      BOOST_CHECK_EQUAL(machine2Configuration1->getOutputEachMinute(), 8);

      auto machine2Configuration1PreviousMachines = machine2Configuration1->getPreviousMachines();
      BOOST_REQUIRE_EQUAL(machine2Configuration1PreviousMachines.size(), 1);

      { // machine2 --> machineConfiguration[0] --> previousMachine[0]
        auto machine2Configuration1PreviousMachine1 = machine2Configuration1PreviousMachines[0];

        BOOST_CHECK_EQUAL(machine2Configuration1PreviousMachine1->getMachineId(), machine1Id);
        BOOST_CHECK_EQUAL(machine2Configuration1PreviousMachine1->getNeededProducts(), 7);
        BOOST_CHECK_EQUAL(machine2Configuration1PreviousMachine1->getInputBufferSize(), 35);
      }
    }

    { // machine2 --> machineConfiguration[1]
      auto machine2Configuration2 = machine2Configurations[1];

      BOOST_CHECK_EQUAL(machine2Configuration2->getProductId(), 88);
      BOOST_CHECK_EQUAL(machine2Configuration2->getOutputEachMinute(), 8);

      auto machine2Configuration2PreviousMachines = machine2Configuration2->getPreviousMachines();
      BOOST_REQUIRE_EQUAL(machine2Configuration2PreviousMachines.size(), 1);

      { // machine2 --> machineConfiguration[1] --> previousMachine[0]
        auto machine2Configuration2PreviousMachine1 = machine2Configuration2PreviousMachines[0];

        BOOST_CHECK_EQUAL(machine2Configuration2PreviousMachine1->getMachineId(), machine1Id);
        BOOST_CHECK_EQUAL(machine2Configuration2PreviousMachine1->getNeededProducts(), 8);
        BOOST_CHECK_EQUAL(machine2Configuration2PreviousMachine1->getInputBufferSize(), 40);
      }
    }
  }
}

// Einde public method tests
BOOST_AUTO_TEST_SUITE_END()

// Testen van public methods van controller
BOOST_AUTO_TEST_SUITE(ProductionControlTestControllerNetwork)

BOOST_AUTO_TEST_CASE(SendTurnOn) {
  std::string configurationFilePath = "./test_configs/test_config_two_machines.yaml";

  // Create server and client
  auto machineEndpoint = std::make_shared<testutils::MockNetwork>();
  auto productionServer = std::make_shared<testutils::MockNetwork>();

  // Start server, start client, wait for connection on server
  productionServer->startMockPCServerController();
  machineEndpoint->startMockMCClientController();
  productionServer->awaitClientConnecting();

  // Get the simulation machine and set its connection
  simulation::SimulationController controller;
  BOOST_REQUIRE_NO_THROW(controller.setConfiguration(configurationFilePath));

  auto application = controller.getApplication();
  BOOST_REQUIRE(application);

  auto machine = application->getMachine(machine1Id);
  BOOST_REQUIRE(machine);

  auto simulationMachine = std::dynamic_pointer_cast<simulation::SimulationMachine>(machine);
  BOOST_REQUIRE(simulationMachine);

  simulationMachine->setSimulationConnection(productionServer->getConnection());

  // prepare test on machine control when message will receive
  testutils::OnMessageFn callback = [](network::Message &message){
    BOOST_CHECK_EQUAL(message.getMessageType(), network::Protocol::kSimMessageTypeTurnOn);
  };

  machineEndpoint->setOnMessageFn(callback);
  simulationMachine->sendTurnOnCommand();

  // wait for the message received
  machineEndpoint->awaitMessageReceived();

  machineEndpoint->stopClient();
  productionServer->stopServer();
}

BOOST_AUTO_TEST_CASE(SendTurnOff) {
  std::string configurationFilePath = "./test_configs/test_config_two_machines.yaml";

  // Create server and client
  auto machineEndpoint = std::make_shared<testutils::MockNetwork>();
  auto productionServer = std::make_shared<testutils::MockNetwork>();

  // Start server, start client, wait for connection on server
  productionServer->startMockPCServerController();
  machineEndpoint->startMockMCClientController();
  productionServer->awaitClientConnecting();

  // Get simulation machine and set its connection
  simulation::SimulationController controller;
  BOOST_REQUIRE_NO_THROW(controller.setConfiguration(configurationFilePath));

  auto application = controller.getApplication();
  BOOST_REQUIRE(application);

  auto machine = application->getMachine(machine1Id);
  BOOST_REQUIRE(machine);

  auto simulationMachine = std::dynamic_pointer_cast<simulation::SimulationMachine>(machine);
  BOOST_REQUIRE(simulationMachine);

  simulationMachine->setSimulationConnection(productionServer->getConnection());

  // prepare test on machine control when message will receive
  testutils::OnMessageFn callback = [](network::Message &message){
    BOOST_CHECK_EQUAL(message.getMessageType(), network::Protocol::kSimMessageTypeTurnOff);
  };

  BOOST_REQUIRE_NO_THROW(machineEndpoint->setOnMessageFn(callback));
  BOOST_REQUIRE_NO_THROW(simulationMachine->sendTurnOffCommand());

  // wait for the message received
  machineEndpoint->awaitMessageReceived();

  machineEndpoint->stopClient();
  productionServer->stopServer();
}

// TODO !!! Move this to application_test after Bas has committed & merged it with dev
BOOST_AUTO_TEST_CASE(SendTurnReconfigure) {
  std::string configurationFilePath = "./test_configs/test_config_two_machines.yaml";

  // Create server and client
  auto machineEndpoint = std::make_shared<testutils::MockNetwork>();
  auto productionServer = std::make_shared<testutils::MockNetwork>();

  // Start server, start client, wait for connection on server
  productionServer->startMockPCServerApplication();
  machineEndpoint->startMockMCClientApplication();
  productionServer->awaitClientConnecting();

  // Get simulation machine and set its connection
  simulation::SimulationController controller;
  BOOST_REQUIRE_NO_THROW(controller.setConfiguration(configurationFilePath));

  auto application = controller.getApplication();
  BOOST_REQUIRE(application);

  auto machine = application->getMachine(machine1Id);
  BOOST_REQUIRE(machine);

  auto simulationMachine = std::dynamic_pointer_cast<simulation::SimulationMachine>(machine);
  BOOST_REQUIRE(simulationMachine);

  simulationMachine->setSimulationConnection(productionServer->getConnection());

  // prepare test on machine control when message will receive
  testutils::OnMessageFn callback = [](network::Message &message){
    BOOST_CHECK_EQUAL(message.getMessageType(), network::Protocol::kAppMessageTypeReconfigure);
    BOOST_CHECK_EQUAL(message.getBodyObject<uint16_t>(), 1);
  };

  machineEndpoint->setOnMessageFn(callback);
  simulationMachine->sendConfigureMessage(1);

  // wait for the message received
  machineEndpoint->awaitMessageReceived();

  machineEndpoint->stopClient();
  productionServer->stopServer();
}

// Einde public method tests
BOOST_AUTO_TEST_SUITE_END()
