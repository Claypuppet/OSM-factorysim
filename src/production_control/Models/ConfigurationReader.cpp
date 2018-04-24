#include "ConfigurationReader.h"

namespace models {

    ConfigurationReader::ConfigurationReader() {
    }

    ConfigurationReader::~ConfigurationReader() {
    }

    void ConfigurationReader::readConfigurationFile(std::string filePath, Configuration &configuration) {
        YAML::Node yamlFileNode = YAML::LoadFile(filePath);
        configuration.deserialize(yamlFileNode);
    }

}