#include "ConfigurationReader.h"

namespace ConfigLoader {

    ConfigurationReader::ConfigurationReader() {
    }

    ConfigurationReader::~ConfigurationReader() {
    }

    void ConfigurationReader::readConfigurationFile(std::string filePath, Models::Configuration &configuration) {
        YAML::Node yamlFileNode = YAML::LoadFile(filePath);
        configuration.deserialize(yamlFileNode);
    }

}