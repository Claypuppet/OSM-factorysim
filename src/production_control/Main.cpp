

#include <utils/Logger.h>
#include <utils/FileLogger.h>
#include "utils/CommandLineArguments.h"
#include "ResultLogger.h"
#include "SimulationController.h"

int main(int argc, char** argv)
{
  utils::CommandLineArguments::i().setCommandlineArguments(argc, argv);

  utils::FileLogger::setupLogger("simulationtest.log", 5);
  core::ResultLogger::setProductionDebugOutput(true);
  core::ResultLogger::getInstance().LogProductionEvent(1, 10);

  simulation::SimulationController controller;
  controller.execute();

	return 0;
}


