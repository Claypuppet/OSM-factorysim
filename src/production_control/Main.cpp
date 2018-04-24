#include "ConfigurationReader.h"
#include <models/Configuration.h>

int main(int argc, char** argv) {
    std::string fileName = argv[1];

    Models::Configuration configuration;
    ConfigurationReader::getInstance().readConfigurationFile(fileName, configuration);

	return 0;
}
