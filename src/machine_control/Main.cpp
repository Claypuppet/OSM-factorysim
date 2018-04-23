/*
 * Author: OSM Projectteam 3
 */


#include <iostream>
#include <memory>
#include <network/Manager.h>
#include <network/Server.h>
#include <network/Client.h>
#include "NetworkComponent.h"


class TempProdControlServer : public Network::IConnectionHandler {
public:
	TempProdControlServer() = default;
	~TempProdControlServer() = default;
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



	// This machine
	Network::Manager manager;
	manager.setRemoteHost("192.168.137.20");
	auto clientThread = manager.runServiceThread();
	Communication::NetworkComponent Network;
	auto client = manager.createClient(std::make_shared<Communication::NetworkComponent>(Network));


//	if(server->isRunning())
//	{
//		std::cout << "server running, try to connect client to server" << std::endl;
		client->start();


		while(!Network.getConnection()){}  // Wait for client to connect

		Network.sendHello();
//	}
//
//	serverThread->join();
	clientThread->join();

	return 0;
}
