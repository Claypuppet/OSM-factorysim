

#include <utils/Logger.h>
#include <utils/FileLogger.h>
#include "utils/CommandLineArguments.h"
#include "ResultLogger.h"
#include "SimulationController.h"

int main(int argc, char** argv)
{
  utils::CommandLineArguments::i().setCommandlineArguments(argc, argv);


//  utils::Time::getInstance().setType(utils::customTime);
//  utils::Time::getInstance().setCurrentTime(0);

  utils::FileLogger::setupLogger("test.log");

  core::ResultLogger::getInstance().setProductionDebugOutput(false);
  core::ResultLogger::getInstance().LogProductionEvent(1, 10);

  core::ResultLogger::getInstance().setProductionDebugOutput(true);
  utils::FileLogger::both()->error("error");
  utils::FileLogger::both()->error("error");
  utils::FileLogger::both()->error("error");
  utils::FileLogger::both()->error("error");
  utils::FileLogger::both()->error("error");
  utils::FileLogger::both()->error("error");

  simulation::SimulationController controller;
  controller.execute();

	return 0;
}


