

#include <utils/Logger.h>
#include <utils/FileLogger.h>
#include "utils/CommandLineArguments.h"
#include "SimulationController.h"

int main(int argc, char **argv) {
  utils::CommandLineArguments::i().setCommandlineArguments(argc, argv);
  simulation::SimulationController controller;
  controller.execute();
  return 0;
}


