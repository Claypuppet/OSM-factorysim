#include "ConfigurationReader.h"
#include "Configuration.h"

int main(int argc, char** argv) {
    std::string fileName = argv[1];

    models::Configuration configuration;
    models::ConfigurationReader::getInstance().readConfigurationFile(fileName, configuration);

	return 0;
}
