/*
 * Test Production Control - Controller
 */


// http://www.boost.org/doc/libs/1_60_0/libs/test/doc/html/boost_test/adv_scenarios/shared_lib_customizations/entry_point.html

#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

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
  utils::FileLogger::getInstance().setupLogger("testlog.log", true);

  for (uint16_t i = 0; i < 100; ++i) {
    utils::FileLogger::getInstance().logToFile("test" + std::to_string(i));
  }

  utils::FileLogger::getInstance().newFile("newtestLog.log", true);

  utils::FileLogger::getInstance().changePattern("(%v)");

  for (uint16_t i = 0; i < 100; ++i) {
    core::ResultLogger::getInstance().machineStatusUpdate(i, models::Machine::kMachineStatusIdle);
  }
  // check if testlog and newtestlog file exist
}



// Einde public method tests
BOOST_AUTO_TEST_SUITE_END()
