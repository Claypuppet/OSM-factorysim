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


// Testen van events naar states (set state, add event, run, check new state)
BOOST_AUTO_TEST_SUITE(ProductionControlTestLogger)

BOOST_AUTO_TEST_CASE(TestProductionLogger) {
  BOOST_REQUIRE_EQUAL(2, 2);
}

BOOST_AUTO_TEST_CASE(SetupLogger) {
  utils::Time::getInstance().setType(utils::customTime);
  utils::Time::getInstance().setCurrentTime(0);

  utils::FileLogger::setupLogger("log", true);

  utils::FileLogger::both()->warn("testlog", true);
  utils::FileLogger::newFile("newLog", true);
  utils::FileLogger::changePattern("(%v)");
  utils::FileLogger::both()->warn("testlog2");

  for (int i = 0; i < 10000000; ++i) {
    utils::FileLogger::file()->info("test" + std::to_string(i));
  }
}



// Einde public method tests
BOOST_AUTO_TEST_SUITE_END()
