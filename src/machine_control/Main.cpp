/*
 * Author: OSM Projectteam 3
 */


#include <iostream>
#include <memory>
#include <network/Manager.h>
#include "NetworkComponent.h"
#include <network/Server.h>


int main( 	int argc,
			char** argv)
{
	std::cout << "Hello from app machine simulator!" << std::endl;

	network::Manager manager = network::Manager();
	auto serverThread = manager.runServiceThread();
	manager.setLocalPort(12345);

	auto network = NetworkComponent();

	auto server = manager.createServer(std::make_shared<NetworkComponent>(network), 32);

	server->start();

	while(server->isRunning())
	{}

	return 0;
}
