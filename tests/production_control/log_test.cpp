/*
 * Test Production Control - Controller
 */


// http://www.boost.org/doc/libs/1_60_0/libs/test/doc/html/boost_test/adv_scenarios/shared_lib_customizations/entry_point.html

#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <network/Client.h>
#include <patterns/notifyobserver/Notifier.hpp>
#include <spdlog/spdlog.h>
#include <utils/time/Time.h>
#include "utils/FileLogger.h"
#include "utils/Logger.h"
#include "../../src/production_control/ResultLogger.h"


// Testen van events naar states (set state, add event, run, check new state)
BOOST_AUTO_TEST_SUITE(ProductionControlTestLogger)


BOOST_AUTO_TEST_CASE(SetupLogger) {
  utils::Time::getInstance().setType(utils::customTime);
  utils::Time::getInstance().syncTime(0);
  auto &fileLogger = utils::FileLogger::getInstance();

  auto logger = fileLogger.addFileLogger("testlogger", "./test.log", true);

  for (uint16_t i = 0; i < 100; ++i) {
    logger->info("test " + std::to_string(i));
  }
  logger->flush();

  // test if test file exists
  BOOST_CHECK(boost::filesystem::exists("./test.log"));

  auto &resultLogger = core::ResultLogger::getInstance();

  std::string configName = "TestConfig2Machines";

  // Creates
  resultLogger.initializeLog("./test_configs/test_config_two_machines.yaml", configName);
  BOOST_CHECK(boost::filesystem::exists(configName));
  BOOST_CHECK(boost::filesystem::exists(configName + "/daily_logs"));

  for (uint16_t i = 0; i < 100; ++i) {
    resultLogger.machineStatusUpdate(i, models::Machine::kMachineStatusIdle);
  }
  // check if daily log exists
  BOOST_CHECK(boost::filesystem::exists(configName + "/daily_logs/1970_01_01-log.yaml"));
}



// Einde public method tests
BOOST_AUTO_TEST_SUITE_END()
