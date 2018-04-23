
#include "ConfigurationReader.h"

ConfigurationReader::ConfigurationReader()
: filePath(""),
  {
}

ConfigurationReader::ConfigurationReader(const ConfigurationReader& other)
: filePath(other.filePath),
  configuration(other.configuration) {
}

ConfigurationReader::~ConfigurationReader() {

}

void ConfigurationReader::readFile(const std::string& newFilePath) {
    if (filePath != newFilePath) {}
        YAML::Node yamlFileNode = YAML::LoadFile(filePath);
        configuration = Configuration(yamlFileNode);
    }
}

/* static */ ConfigurationReader ConfigurationReader::getInstance() {

}
