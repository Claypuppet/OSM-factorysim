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
  controller.setConfiguration("./test_configs/test_config_two_machines.yaml");
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

  app->saveMachineStatistics();

  machine->setStatus(models::Machine::kMachineStatusConfiguring);
  machine->prepareReconfigure(12);

  machine->setStatus(models::Machine::kMachineStatusIdle);

  // Producing 200 products with id 12
  for(uint8_t i = 0; i < 200; ++i){
    machine->takeProductsFromInputBuffers();
    machine->placeProductsInOutputBuffer();
    machine->getCurrentOutputBuffer()->takeFromBuffer(1);
  }

  machine->setStatus(models::Machine::kMachineStatusConfiguring);
  machine->prepareReconfigure(88);

  machine->setStatus(models::Machine::kMachineStatusIdle);

  // Producing 150 products with id 88
  for(uint8_t i = 0; i < 150; ++i){
    machine->takeProductsFromInputBuffers();
    machine->placeProductsInOutputBuffer();
    machine->getCurrentOutputBuffer()->takeFromBuffer(1);
  }

  //Setting time spend in state
  utils::Time::getInstance().syncTime(30000);
  machine->setStatus(models::Machine::kMachineStatusConfiguring);
  utils::Time::getInstance().syncTime(31500);
  machine->setStatus(models::Machine::kMachineStatusIdle);
  utils::Time::getInstance().syncTime(42000);
  machine->setStatus(models::Machine::kMachineStatusProcessingProduct);
  utils::Time::getInstance().syncTime(50000);
  machine->setStatus(models::Machine::kMachineStatusBroken);
  utils::Time::getInstance().syncTime(60000);
  machine->setStatus(models::Machine::kMachineStatusConfiguring);

  // Check if stats get reset
  app->saveMachineStatistics();

  machine->setStatus(models::Machine::kMachineStatusConfiguring);
  machine->prepareReconfigure(12);

  machine->setStatus(models::Machine::kMachineStatusIdle);

  // Producing 180 products with id 12
  for(uint8_t i = 0; i < 180; ++i){
    machine->takeProductsFromInputBuffers();
    machine->placeProductsInOutputBuffer();
    machine->getCurrentOutputBuffer()->takeFromBuffer(1);
  }

  machine->setStatus(models::Machine::kMachineStatusConfiguring);
  machine->prepareReconfigure(88);

  machine->setStatus(models::Machine::kMachineStatusIdle);

  // Producing 110 products with id 88
  for(uint8_t i = 0; i < 110; ++i){
    machine->takeProductsFromInputBuffers();
    machine->placeProductsInOutputBuffer();
    machine->getCurrentOutputBuffer()->takeFromBuffer(1);
  }

  //Setting time spend in state
  utils::Time::getInstance().syncTime(60000);
  machine->setStatus(models::Machine::kMachineStatusConfiguring);
  utils::Time::getInstance().syncTime(62000);
  machine->setStatus(models::Machine::kMachineStatusIdle);
  utils::Time::getInstance().syncTime(72000);
  machine->setStatus(models::Machine::kMachineStatusProcessingProduct);
  utils::Time::getInstance().syncTime(83000);
  machine->setStatus(models::Machine::kMachineStatusBroken);
  utils::Time::getInstance().syncTime(90000);
  machine->setStatus(models::Machine::kMachineStatusConfiguring);

  // Check if stats get reset
  app->saveMachineStatistics();

  machine->setStatus(models::Machine::kMachineStatusConfiguring);
  machine->prepareReconfigure(12);

  machine->setStatus(models::Machine::kMachineStatusIdle);

  // Producing 210 products with id 12
  for(uint8_t i = 0; i < 210; ++i){
    machine->takeProductsFromInputBuffers();
    machine->placeProductsInOutputBuffer();
    machine->getCurrentOutputBuffer()->takeFromBuffer(1);
  }

  machine->setStatus(models::Machine::kMachineStatusConfiguring);
  machine->prepareReconfigure(88);

  machine->setStatus(models::Machine::kMachineStatusIdle);

  // Producing 170 products with id 88
  for(uint8_t i = 0; i < 170; ++i){
    machine->takeProductsFromInputBuffers();
    machine->placeProductsInOutputBuffer();
    machine->getCurrentOutputBuffer()->takeFromBuffer(1);
  }

  //Setting time spend in state
  utils::Time::getInstance().syncTime(90000);
  machine->setStatus(models::Machine::kMachineStatusConfiguring);
  utils::Time::getInstance().syncTime(92500);
  machine->setStatus(models::Machine::kMachineStatusIdle);
  utils::Time::getInstance().syncTime(101000);
  machine->setStatus(models::Machine::kMachineStatusProcessingProduct);
  utils::Time::getInstance().syncTime(109000);
  machine->setStatus(models::Machine::kMachineStatusBroken);
  utils::Time::getInstance().syncTime(120000);
  machine->setStatus(models::Machine::kMachineStatusConfiguring);

  // Check if stats get reset
  app->saveMachineStatistics();
  
  app->logStatistics();
}


BOOST_AUTO_TEST_SUITE_END()