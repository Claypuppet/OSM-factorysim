//
// Created by don on 30-5-18.
//

#include <boost/test/unit_test.hpp>
#include <iostream>
#include "../../src/visualizer/Events/Event.h"
#include "../../src/visualizer/FileReader.h"
#include "../../src/visualizer/Events/BufferUpdateEvent.h"
#include "../../src/visualizer/Events/StatusUpdateEvent.h"
#include "../../src/visualizer/Events/ConfigUpdateEvent.h"

BOOST_AUTO_TEST_SUITE(Visualiser_File_Reader_Tests)

BOOST_AUTO_TEST_CASE(File_Reader_Events) {
  std::vector<visualisercore::EventPtr> events;

  file::FileReader reader;
  reader.deserializeEvents("./test_results/Kleine_productiestraat.yaml", events);

  BOOST_REQUIRE(events.size() == 10);

  BOOST_CHECK(events[0]->getTime() == 1514786400000);
  BOOST_CHECK(events[3]->getMachineId() == 1);
  BOOST_REQUIRE(std::dynamic_pointer_cast<visualisercore::BufferUpdateEvent>(events[7]));
  BOOST_REQUIRE(std::dynamic_pointer_cast<visualisercore::StatusUpdateEvent>(events[0]));
  BOOST_REQUIRE(std::dynamic_pointer_cast<visualisercore::ConfigUpdateEvent>(events[2]));
  BOOST_CHECK(std::dynamic_pointer_cast<visualisercore::BufferUpdateEvent>(events[7])->getProductId() == 1);
  BOOST_CHECK(std::dynamic_pointer_cast<visualisercore::BufferUpdateEvent>(events[7])->getBufferAmount() == 1);
  BOOST_CHECK(std::dynamic_pointer_cast<visualisercore::StatusUpdateEvent>(events[0])->getStatusUpdateType()
                  == models::Machine::MachineStatus::kMachineStatusConfiguring);
  BOOST_CHECK(std::dynamic_pointer_cast<visualisercore::ConfigUpdateEvent>(events[2])->getConfigId() == 1);
}

BOOST_AUTO_TEST_CASE(Visualiser_Reader_Machines) {

  file::FileReader reader;
  auto config = reader.deserializeSimConfig("./test_results/Kleine_productiestraat.yaml");

  auto machines = config->getProductionLine()->getMachines();
  BOOST_REQUIRE_EQUAL(machines.size(), 2);

  BOOST_REQUIRE(machines.size() == 2);
  BOOST_CHECK(machines[0]->getName() == "Zaagmachine (hout)");
  BOOST_CHECK(machines[1]->getName() == "Voorboormachine (hout)");
  BOOST_CHECK(machines[0]->getId() == 1);
  BOOST_CHECK(machines[1]->getId() == 2);

  { // machines[0]
    auto machine = machines[0];

    auto machineConfigurations = machine->getConfigurations();
    BOOST_REQUIRE_EQUAL(machineConfigurations.size(), 2);

    BOOST_CHECK_EQUAL(machine->getInitializationDurationInSeconds(), 6);
    BOOST_CHECK_EQUAL(machine->getInitializationDurationInMilliseconds(), 6000);
    BOOST_CHECK_EQUAL(machine->getReparationTimeInMinutes(), 24);
    BOOST_CHECK_EQUAL(machine->getReparationTimeStddevInMinutes(), 30);
    BOOST_CHECK_EQUAL(machine->getMeanTimeBetweenFailureInHours(), 9800);

    { // machines[0].configurations[0]
      auto machineConfiguration = machineConfigurations[0];

      auto previousMachines = machineConfiguration->getPreviousMachines();
      BOOST_REQUIRE_EQUAL(previousMachines.size(), 1);

      BOOST_CHECK_EQUAL(machineConfiguration->getProductId(), 2);
      BOOST_CHECK_EQUAL(machineConfiguration->getOutputEachMinute(), 12);
      BOOST_CHECK_EQUAL(machineConfiguration->getProcessTime(), 60000 / 8);

      { // machines[0].configurations[0].previousmachines[0]
        auto previousMachine = previousMachines[0];

        BOOST_CHECK_EQUAL(previousMachine->getMachineId(), 0);
        BOOST_CHECK_EQUAL(previousMachine->getNeededProducts(), 1);
        BOOST_CHECK_EQUAL(previousMachine->getInputBufferSize(), 4);
      }
    }
  }
}

BOOST_AUTO_TEST_SUITE_END()