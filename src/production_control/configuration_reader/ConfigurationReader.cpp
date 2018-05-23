#include "ConfigurationReader.h"

namespace ConfigLoader {

/* static */ ConfigurationReader &ConfigurationReader::getInstance(Strategy strategy) {
  ConfigurationReader &instance = Singleton::getInstance();
  instance.setStrategy(strategy);
  return instance;
}

models::Configuration ConfigurationReader::deserializeConfigurationFile(const std::string& filePath) {
  models::Configuration configuration;
  strategy.deserializeConfigurationFile(filePath, configuration);
  return configuration;
}

void ConfigurationReader::setStrategy(Strategy strategy) {
  this->strategy = strategy;
}

}