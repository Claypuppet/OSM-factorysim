#include "ConfigurationReader.h"

namespace ConfigLoader {

ConfigurationReader::ConfigurationReader() {
}

ConfigurationReader::~ConfigurationReader() {
}

void ConfigurationReader::readConfigurationFile(std::string filePath, models::Configuration &configuration) {
  YAML::Node yamlFileNode = YAML::LoadFile(filePath);
  try {
	configuration.deserialize(yamlFileNode);
  }
  catch (const std::exception &e) {
	std::cerr << "Invalid config file read: " << e.what() << std::endl;
  }
}

}