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

const std::string ConfigurationReader::getFileExtension(const std::string & filePath) const {
  return filePath.substr(filePath.find_last_of(".") + 1);
}

const std::shared_ptr<models::Configuration> ConfigurationReader::deserialize(const std::string &filePathString) {
  const std::string fileExtension = getFileExtension(filePathString);

  if (fileExtension == "json") {

    // YAML Is a subset of JSON so the YAML library
    // is also able to read a JSON file
    setStrategy(YAMLStrategyType);

  } else if (fileExtension == "yaml") {

    setStrategy(YAMLStrategyType);

  } else {

    std::cerr << "Given file format not supported" << std::endl;

  }

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