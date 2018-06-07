//
// Created by don on 6-6-18.
//

#include <boost/test/unit_test.hpp>
#include <utils/time/Time.h>
#include "../../src/production_control/SimulationController.h"
#include "../../src/production_control/ResultLogger.h"

BOOST_AUTO_TEST_SUITE(ProductionControlMachineTests)

BOOST_AUTO_TEST_CASE(MachineTestWeeklyStatistics){
  simulation::SimulationController controller;
  controller.setConfiguration("test_configs/test_config_two_machines.yaml");
  auto app = controller.getApplication();

  auto machine = app->getMachine(15);

  utils::Time::getInstance().setType(utils::TimeType::customTime);
  utils::Time::getInstance().syncTime(0);

  machine->setStatus(models::Machine::kMachineStatusConfiguring);
  machine->prepareReconfigure(12);

  machine->setStatus(models::Machine::kMachineStatusIdle);

  // Producing 100 products with id 12
  for(uint8_t i = 0; i < 100; ++i){
    machine->takeProductsFromInputBuffers();
    machine->placeProductsInOutputBuffer();
    machine->getCurrentOutputBuffer()->takeFromBuffer(1);
  }

  machine->setStatus(models::Machine::kMachineStatusConfiguring);
  machine->prepareReconfigure(88);

  machine->setStatus(models::Machine::kMachineStatusIdle);

  // Producing 50 products with id 88
  for(uint8_t i = 0; i < 50; ++i){
    machine->takeProductsFromInputBuffers();
    machine->placeProductsInOutputBuffer();
    machine->getCurrentOutputBuffer()->takeFromBuffer(1);
  }

  //Setting time spend in state
  utils::Time::getInstance().syncTime(0);
  machine->setStatus(models::Machine::kMachineStatusConfiguring);
  utils::Time::getInstance().syncTime(1000);
  machine->setStatus(models::Machine::kMachineStatusIdle);
  utils::Time::getInstance().syncTime(10000);
  machine->setStatus(models::Machine::kMachineStatusProcessingProduct);
  utils::Time::getInstance().syncTime(25000);
  machine->setStatus(models::Machine::kMachineStatusBroken);
  utils::Time::getInstance().syncTime(30000);
  machine->setStatus(models::Machine::kMachineStatusConfiguring);

  // Getting stats of the first week
  machine->addWeeklyStatistics();

  auto stats = machine->getWeeklyStatistics()[0];
  auto producedProducts = stats.getProducedProducts();

  BOOST_CHECK(producedProducts[12] == 100);
  BOOST_CHECK(producedProducts[88] == 50);
  BOOST_CHECK(stats.getDownTime() == 5000);
  BOOST_CHECK(stats.getConfigureTime() == 1000);
  BOOST_CHECK(stats.getIdleTime() == 9000);
  BOOST_CHECK(stats.getProductionTime() == 15000);

  // Check if stats get reset
  machine->addWeeklyStatistics();

  stats = machine->getWeeklyStatistics()[1];
  producedProducts = stats.getProducedProducts();

  BOOST_CHECK(producedProducts[12] == 0);
  BOOST_CHECK(producedProducts[88] == 0);
  BOOST_CHECK(stats.getDownTime() == 0);
  BOOST_CHECK(stats.getConfigureTime() == 0);
  BOOST_CHECK(stats.getIdleTime() == 0);
  BOOST_CHECK(stats.getProductionTime() == 0);

  core::ResultLogger::getInstance().logStatistics(app->getMachines());
}


BOOST_AUTO_TEST_SUITE_END()