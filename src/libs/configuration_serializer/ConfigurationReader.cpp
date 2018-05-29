#include "ConfigurationReader.h"

namespace configurationserializer {

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
    setStrategy(JSONStrategyType);

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
      strategy = std::make_shared<JSONStrategy>(JSONStrategy());
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