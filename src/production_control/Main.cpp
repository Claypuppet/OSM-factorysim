#include "ConfigurationReader.h"
#include <models/Configuration.h>
#include <iostream>
#include <memory>
#include <Logger/Logger.h>
#include "network/Manager.h"
#include "AppConnectionHandler.h"
#include "network/Server.h"
#include "network/Client.h"
#include "network/Connection.h"
#include "network/Protocol.h"
#include "TestConnectionHandler.h"

int main( 	int argc,
			char** argv)
{
	Core::Application app;
	app.startServer();

//    std::string fileName = argv[1];
//    Models::Configuration configuration;
//    ConfigurationReader::getInstance().readConfigurationFile(fileName, configuration);



	Network::Manager clientManager;
	ThreadPtr clientThread = clientManager.runServiceThread();
	Network::ClientPtr client = clientManager.createClient(std::make_shared<TestConnectionHandler>());

	if(app.isServerRunning())
	{
		client->start();
		while(!client->getConnection())
        {

        }
        if(client->getConnection()) {
			Network::Message msg(Network::Protocol::kAppMessageTypeRegisterMachine, "5");
			client->getConnection()->writeMessage(msg);
		}
		Network::Message msg(2, "test");
		while(!app.getMachine(5))
        {

        }
		if(app.getMachine(5)->isConnected()) {
            app.getMachine(5)->sendMessage(msg);
        }
	}

	clientThread->join();

	app.joinServerThread();

	return 0;
}
