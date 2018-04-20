/*
 * Author: OSM Projectteam 3
 */


#include <iostream>
#include <memory>
#include <network/Manager.h>
#include <network/Server.h>
#include <network/Client.h>
#include "NetworkComponent.h"


class TempProdControlServer : public network::IConnectionHandler {
public:
	TempProdControlServer() = default;
	~TempProdControlServer() = default;
protected:

	void onConnectionFailed(network::ConnectionPtr connection, const boost::system::error_code &error) override {
		IConnectionHandler::onConnectionFailed(connection, error);
	}

	void onConnectionEstablished(network::ConnectionPtr connection) override {

	}

	void onConnectionDisconnected(network::ConnectionPtr connection, const boost::system::error_code &error) override {

	}

	void onConnectionMessageReceived(network::ConnectionPtr connection, network::Message &message) override {
		std::cout << "Server recieved: " << message.mBody << std::endl;
	}

	void onConnectionMessageSent(network::ConnectionPtr connection, network::Message &message) override {
		IConnectionHandler::onConnectionMessageSent(connection, message);
	}

};

int main( 	int argc,
			char** argv)
{
	std::cout << "Hello from app machine simulator!" << std::endl;

	// Temp server production control
//	network::Manager serverManager;
//	auto serverThread = serverManager.runServiceThread();
//	TempProdControlServer serverController;
//	auto server = serverManager.createServer(std::make_shared<TempProdControlServer>(serverController), 32);
//	server->start();



	// This machine
	network::Manager manager;
	manager.setRemoteHost("192.168.137.20");
	auto clientThread = manager.runServiceThread();
	NetworkComponent network;
	auto client = manager.createClient(std::make_shared<NetworkComponent>(network));


//	if(server->isRunning())
//	{
//		std::cout << "server running, try to connect client to server" << std::endl;
		client->start();


		while(!network.getConnection()){}  // Wait for client to connect

		network.sendHello();
//	}
//
//	serverThread->join();
	clientThread->join();

	return 0;
}
