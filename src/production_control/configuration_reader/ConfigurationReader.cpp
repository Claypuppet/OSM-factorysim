#include "ConfigurationReader.h"

namespace ConfigLoader {

ConfigurationReader::ConfigurationReader(const ConfigurationReader &other)
    : strategy(other.strategy){
}

///* static */ ConfigurationReader &ConfigurationReader::getInstance(StrategyType strategyType) {
//  ConfigurationReader &instance = Singleton::getInstance();
//  instance.setStrategy(strategyType);
//  return instance;
//}

std::shared_ptr<models::Configuration> ConfigurationReader::deserialize(const std::string &filePathString) {
//  boost::filesystem::path filePath(filePathString);
//  std::string fileExtension = filePath.extension().string();
//  boost::algorithm::to_lower(fileExtension);
//
//  if (fileExtension == ".json") {
//
//    setStrategy(JSONStrategyType);
//
//  } else if (fileExtension == ".yaml") {
//
//    setStrategy(YAMLStrategyType);
//
//  }

  // because file extension recognision is not supported
  // we use a default strategy.
  setStrategy(YAMLStrategyType);
  return strategy->deserialize(filePathString);
}

void ConfigurationReader::setStrategy(StrategyType strategyType) {
  switch(strategyType) {
    case JSONStrategyType:
      // Because YAML is a subset of JSON, the YAML library
      // is able to read json to. Therefor we use the YAMLStrategy
      // to read JSON configuration files
      strategy = std::make_shared<YAMLStrategy>(YAMLStrategy());
      break;

    case YAMLStrategyType:
      strategy = std::make_shared<YAMLStrategy>(YAMLStrategy());
      break;

    default:
      strategy = nullptr;
      break;
  }
}

}