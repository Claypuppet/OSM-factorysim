//
// Created by don on 5-6-18.
//

#include <boost/test/unit_test.hpp>
#include "../../src/production_control/Application.h"
#include "../../src/production_control/states_application/InOperationState.h"
#include "../../src/production_control/SimulationController.h"
#include "../../src/production_control/states_application/in_operation/OperatingState.h"

BOOST_AUTO_TEST_SUITE(InOperationStateTests);

BOOST_AUTO_TEST_CASE(BufferUpdateTest){

  simulation::SimulationController controller;

  //Setting config
  controller.setConfiguration("test_configs/test_config_two_machines.yaml");

  auto app = controller.getApplication();

  auto machine1 = app->getMachine(15);
  auto machine2 = app->getMachine(75);

  //Check if config is set
  BOOST_REQUIRE(machine1 && machine2);

  //Configuring machines
  machine1->setStatus(models::Machine::MachineStatus::kMachineStatusConfiguring);
  machine2->setStatus(models::Machine::MachineStatus::kMachineStatusConfiguring);

  machine1->prepareReconfigure(12);
  machine2->prepareReconfigure(12);

  machine1->setStatus(models::Machine::MachineStatus::kMachineStatusIdle);
  machine2->setStatus(models::Machine::MachineStatus::kMachineStatusIdle);

  //Checking if outputbuffers are configured
  BOOST_REQUIRE(machine1->getCurrentOutputBuffer());
  BOOST_REQUIRE(machine2->getCurrentOutputBuffer());

  // Check if output buffer is empty
  BOOST_CHECK(machine1->getCurrentOutputBuffer()->getAmountInBuffer() == 0);

  //Setting the InOperationState
  app->setCurrentState(std::make_shared<applicationstates::OperatingState>(*app));

  //Scheduling events for processing a product
  auto event = std::make_shared<applicationstates::Event>(applicationstates::EventType::kEventTypeMachineProductTakenFromBuffer);
  event->setArgument(0, machine1->getId());

  for(uint8_t i = 0; i < 5; ++i){
    app->scheduleEvent(event);
  }

  event = std::make_shared<applicationstates::Event>(applicationstates::EventType::kEventTypeMachineProductAddedToBuffer);
  event->setArgument(0, machine1->getId());

  app->scheduleEvent(event);

  app->run();

  //Check if a product is processed
  BOOST_CHECK(machine1->getCurrentOutputBuffer()->getAmountInBuffer() == 1);
}


BOOST_AUTO_TEST_SUITE_END();