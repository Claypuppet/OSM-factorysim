
#include <boost/test/unit_test.hpp>
#include <utils/time/Time.h>
#include "../../src/production_control/SimulationController.h"
#include "../../src/production_control/SimulationMachineLocal.h"
#include "../../src/production_control/ResultLogger.h"
#include "../test_helpers/MockObserver.h"
#include "../../src/production_control/NotificationTypes.h"

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

  app->logFinalStatistics();
}



BOOST_AUTO_TEST_CASE(ProductionControlSimulationMachineLocalBreaking){
  utils::Time::getInstance().setType(utils::TimeType::customTime);
  utils::Time::getInstance().reset();

  uint16_t nTests = 1000;
  uint16_t nFailures = 0;


  testutils::MockObserver observer;

  testutils::NotificationHandlerFn callback = [&nFailures](const patterns::notifyobserver::NotifyEvent &notification){
    if(notification.getEventId() == NotifyEventIds::eApplicationNOK){
      ++nFailures;
    }
  };

  observer.setHandleNotificationFn(callback);

  uint16_t meanTimeBetweenFailureInHours = 250;
  std::vector<models::PreviousMachinePtr> previousMachines;
  previousMachines.push_back(std::make_shared<models::PreviousMachine>());
  models::MachineConfigurationPtr configuration = std::make_shared<models::MachineConfiguration>(1, 1, previousMachines);

  std::vector<models::MachineConfigurationPtr> confVector = {configuration};
  models::Machine modelMachine(1, meanTimeBetweenFailureInHours, 10, 1, 300, nullptr, "", confVector);
  auto machine = std::make_shared<simulation::SimulationMachineLocal>(modelMachine);
  machine->sendConfigureMessage(1);
  machine->addObserver(observer);

  uint64_t millisecondsInHour = 3600000;

  for(uint16_t i = 0; i < nTests; ++i) {
    for (uint16_t j = 0; j < meanTimeBetweenFailureInHours; ++j) {
      machine->sendStartProcessMessage();
      utils::Time::getInstance().increaseCurrentTime(millisecondsInHour);
    }
    utils::Time::getInstance().reset();
    machine->sendTurnOnCommand(); // reset time since last broken
  }

  BOOST_CHECK_GT(nFailures, 0.9*nTests);
  BOOST_CHECK_LT(nFailures, 1.1*nTests);
}


BOOST_AUTO_TEST_SUITE_END()