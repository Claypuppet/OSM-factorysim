#include <models/Configuration.h>
#include <models/MachineConfiguration.h>
#include "SimulationController.h"
#include "ConfigurationReader.h"

int main( 	int argc,
			char** argv)
{
	ConfigLoader::ConfigurationReader reader;
	Models::Configuration inputConfig;
	reader.readConfigurationFile("../configs/configfile.yaml", inputConfig);

	std::string string;

	std::stringstream binaryStream((std::ios::out | std::ios::binary));
	cereal::PortableBinaryOutputArchive outputArchive(binaryStream);
	outputArchive(inputConfig);
	string = binaryStream.str();

	std::cout << string << std::endl;

	Models::Configuration outputConfig;

	std::stringstream binaryStream2((std::ios::in | std::ios::binary));
	binaryStream2.str(string);
	cereal::PortableBinaryInputArchive inputArchive(binaryStream2);
	inputArchive(outputConfig);

	std::cout << outputConfig.getName() << std::endl;

	return 0;
}
