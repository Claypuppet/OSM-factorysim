#include <iostream>
#include <memory>

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

  utils::CommandLineArguments::i().setCommandlineArguments(argc, argv);

  models::Machine machine;
  simulator::SimulationController controller(machine);

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