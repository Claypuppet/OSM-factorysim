#include <iostream>
#include <memory>
#include <string>

#include <network/Server.h>
#include <cstdint>

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

  // Set up the machine which is being controlled
  models::Machine machine(std::stoi(machineId.value), "");

  // Create the controller, which is set to the previously created machine
  simulator::SimulationController controller(machine);

  // Start up the controller
  controller.execute();

  return 0;
}

/**
 * Temporary class to start a server for testing purposes
 */
class TempProdControlServer : public Network::IConnectionHandler {
 public:
  TempProdControlServer() = default;
  virtual ~TempProdControlServer() = default;
 protected:

  void onConnectionFailed(Network::ConnectionPtr connection, const boost::system::error_code &error) override {
    IConnectionHandler::onConnectionFailed(connection, error);
  }

  void onConnectionEstablished(Network::ConnectionPtr connection) override {

  }

  void onConnectionDisconnected(Network::ConnectionPtr connection, const boost::system::error_code &error) override {

  }

  void onConnectionMessageReceived(Network::ConnectionPtr connection, Network::Message &message) override {
    std::cout << "Server recieved: " << message.mBody << std::endl;
  }

  void onConnectionMessageSent(Network::ConnectionPtr connection, Network::Message &message) override {
    IConnectionHandler::onConnectionMessageSent(connection, message);
  }

};