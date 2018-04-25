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

//#include "ConfigurationReader.h"

int main( 	int argc,
			char** argv)
{

    std::string fileName = "../configs/configfile.yaml";
    Models::Configuration configuration;
    ConfigLoader::ConfigurationReader::getInstance().readConfigurationFile(fileName, configuration);

    

	return 0;
}
