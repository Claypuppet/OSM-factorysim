#include <iostream>
#include <memory>

#include <network/Server.h>

#include "SimulationController.h"
#include "utils/CommandLineArguments.h"

int main(int argc, char **argv) {

  // Temp server production control
//	Network::Manager serverManager;
//	auto serverThread = serverManager.runServiceThread();
//	TempProdControlServer serverController;
//	auto server = serverManager.createServer(std::make_shared<TempProdControlServer>(serverController), 32);
//	server->start();

  // Ready commandline arguments
  utils::CommandLineArguments::i().setCommandlineArguments(argc, argv);

  // Get the machine's ID from the commandline arguments
  utils::CommandlineArgument machineId = utils::CommandLineArguments::getInstance().getKwarg("-machine_id");

  // Create the controller, which is set to the previously created machine
  simulator::SimulationController controller(std::stoi(machineId.value));

  // Start up the controller
  controller.execute();

  return 0;
}