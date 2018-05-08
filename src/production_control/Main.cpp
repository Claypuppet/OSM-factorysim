

#include "SimulationController.h"
#include "utils/CommandLineArguments.h"


int main(int argc, char** argv)
{
	utils::CommandLineArguments::i().setCommandlineArguments(argc, argv);

	Simulation::SimulationController controller;
	controller.execute();

	return 0;
}


// TODO : move to unit test?

//	ConfigLoader::ConfigurationReader reader;
//	models::Configuration inputConfig;
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
//	models::Configuration outputConfig;
//
//	std::stringstream binaryStream2((std::ios::in | std::ios::binary));
//	binaryStream2.str(string);
//	cereal::PortableBinaryInputArchive inputArchive(binaryStream2);
//	inputArchive(outputConfig);
//
//	std::cout << outputConfig.getName() << std::endl;