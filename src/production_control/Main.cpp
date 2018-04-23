/*
 * Copyright (c) 2015-2016 Joost Kraaijeveld. See license.txt for details.
 * For information, bug reports and additions send an e-mail to ProjectTemplate@Askesis.nl.
 *
 * Author: jkr
 */


#include <iostream>

#include <memory>
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
	Application app;
	app.startServer();



	Network::Manager clientManager;
	ThreadPtr clientThread = clientManager.runServiceThread();
	Network::ClientPtr client = clientManager.createClient(std::make_shared<TestConnectionHandler>());

	if(app.isServerRunning())
	{
		client->start();
//        if(client->getConnection()) {
//			Network::Message msg(Network::Protocol::kAppMessageTypeRegisterMachine, "5");
//			client->getConnection()->writeMessage(msg);
//		}
	}

	clientThread->join();

	app.joinServerThread();

	return 0;
}
