#include <models/Configuration.h>
#include <models/MachineConfiguration.h>
#include <cereal/archives/portable_binary.hpp>
#include "SimulationController.h"
#include "ConfigurationReader.h"
//#include "command_line/CommandLineArguments.h"

int main(int argc, char** argv)
{
	// TODO, set command line arguments
//	CommandLineArguments::i().setCommandlineArguments(argc, argv);
	if(argc == 2){
		std::string simFile(argv[1]);
		Simulation::SimulationController controller(simFile);
		controller.execute();

	}


	// TODO : move to unit test?

//	ConfigLoader::ConfigurationReader reader;
//	Models::Configuration inputConfig;
//	reader.readConfigurationFile("../../configs/configfile.yaml", inputConfig);
//
//	std::string string;
//
//	std::stringstream binaryStream((std::ios::out | std::ios::binary));
//	cereal::PortableBinaryOutputArchive outputArchive(binaryStream);
//	outputArchive(inputConfig);
//	string = binaryStream.str();
//
//	std::cout << string << std::endl;
//
//	Models::Configuration outputConfig;
//
//	std::stringstream binaryStream2((std::ios::in | std::ios::binary));
//	binaryStream2.str(string);
//	cereal::PortableBinaryInputArchive inputArchive(binaryStream2);
//	inputArchive(outputConfig);
//
//	std::cout << outputConfig.getName() << std::endl;

	return 0;
}
