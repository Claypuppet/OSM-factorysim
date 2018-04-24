/*
 * Copyright (c) 2015-2016 Joost Kraaijeveld. See license.txt for details.
 * For information, bug reports and additions send an e-mail to ProjectTemplate@Askesis.nl.
 *
 * Author: jkr
 */


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
#include "SimulationController.h"

int main( 	int argc,
			char** argv)
{
	Core::SimulationController controller;
	controller.run();
	return 0;
}
