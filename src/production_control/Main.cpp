

#include <utils/Logger.h>
#include <utils/FileLogger.h>
#include <utils/time/Time.h>
#include "utils/CommandLineArguments.h"
#include "SimulationController.h"
#include "ResultLogger.h"

int main(int argc, char** argv)
{
  utils::CommandLineArguments::i().setCommandlineArguments(argc, argv);

  utils::Time::getInstance().setType(utils::customTime);
  utils::Time::getInstance().setCurrentTime(0);

  utils::FileLogger::setupLogger("wut.log", true);

  for (int i = 0; i < 100; ++i) {
    utils::FileLogger::both()->info("test" + std::to_string(i));
  }

  utils::FileLogger::newFile("wut2.log", true);

  utils::FileLogger::changePattern("(%v)");


  core::ResultLogger::getInstance().setProductionDebugOutput(true);

  for (int i = 0; i < 100; ++i) {
    core::ResultLogger::LogProductionEvent(i, i);
  }

  simulation::SimulationController controller;
  controller.execute();

	return 0;
}


