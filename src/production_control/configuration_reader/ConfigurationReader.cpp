#include "ConfigurationReader.h"

namespace ConfigLoader {

ConfigurationReader::ConfigurationReader(const ConfigurationReader &other)
    : strategy(other.strategy){
}

/* static */ ConfigurationReader &ConfigurationReader::getInstance(StrategyType strategyType) {
  ConfigurationReader &instance = Singleton::getInstance();
  instance.setStrategy(strategyType);
  return instance;
}

std::shared_ptr<models::Configuration> ConfigurationReader::deserialize(const std::string& filePath) {
  std::string extension = boost::filesystem::extension(filePath);
  std::cout << "filename extension: " << extension << std::endl;
  return strategy->deserialize(filePath);
}

void ConfigurationReader::setStrategy(StrategyType strategyType) {
  switch(strategyType) {
    case JSONStrategyType:
      strategy = std::make_shared<JSONStrategy>(JSONStrategy());
      break;

    default:
      strategy = nullptr;
      break;
  }
}

}