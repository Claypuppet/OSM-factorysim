/*
 * Author: OSM Projectteam 3
 */


#include <iostream>
#include <memory>
#include "SimulationController.h"

#include <network/Server.h>



int main( 	int argc,
			char** argv)
{
	std::cout << "Hello from app machine simulator!" << std::endl;

	// Temp server production control

//	Network::Manager serverManager;
//	auto serverThread = serverManager.runServiceThread();
//	TempProdControlServer serverController;
//	auto server = serverManager.createServer(std::make_shared<TempProdControlServer>(serverController), 32);
//	server->start();



	// This machine controller

	uint16_t machineId;
	std::string machineName;

	std::cout << "What is the machine's ID?" << std::endl;
	std::cin >> machineId;

	std::cout << "What is the machine's name?" << std::endl;
	std::cin >> machineName;

	Simulator::SimulationController controller(Models::Machine(machineId, machineName));

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