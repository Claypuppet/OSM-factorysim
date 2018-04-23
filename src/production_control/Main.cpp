/*
 * Copyright (c) 2015-2016 Joost Kraaijeveld. See license.txt for details.
 * For information, bug reports and additions send an e-mail to ProjectTemplate@Askesis.nl.
 *
 * Author: jkr
 */


#include <iostream>

#include "silly_objects/Lib1.hpp"
#include <memory>
#include "network/Manager.h"
#include "CommNet.h"
#include "network/Server.h"
#include "network/Client.h"
#include "network/Connection.h"

int main( 	int argc,
			char** argv)
{
	Application app;
	app.joinServerThread();
	return 0;
}
