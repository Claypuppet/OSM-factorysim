#ifndef PRODUCTION_LINE_CONTROL_CONFIGFILE_H
#define PRODUCTION_LINE_CONTROL_CONFIGFILE_H

#include <string>
#include <iostream>

#include <patterns/singleton/Singleton.h>

#include "deserialize_strategies/DeserializeStrategy.h"
#include "deserialize_strategies/YAMLStrategy.h"
#include "deserialize_strategies/JSONStrategy.h"

namespace configurationserializer {

enum StrategyType {
  JSONStrategyType,
  YAMLStrategyType
};

/**
 * Singleton class to deserialize configuration files by filePath
 */
class ConfigurationReader : public patterns::singleton::Singleton<ConfigurationReader> {

 public:
  ConfigurationReader() = default;
  virtual ~ConfigurationReader() = default;

  /**
   * Copy this instance of ConfigLoader
   * @param other
   */
  ConfigurationReader(const ConfigurationReader &other);

  /**
   *
   * A function that adds configuration settings into a config object
   * @param filePath : The path the config file
   * @return shared pointer to the configuration model
   */
  const std::shared_ptr<models::Configuration> deserialize(const std::string& filePath);

  /**
   * Get the instance, set the given strategy and return the instance.
   * @param strategy the strategy that instance has to have
   * @return instance with the given strategy
   */
//  static ConfigurationReader &getInstance(StrategyType strategyType);

  /**
   * Set a new strategy
   * @param strategy the new strategy
   */
  void setStrategy(StrategyType strategyType);

 private:
  /**
   * Get the extension of a file path
   * @param filePath filepath ending with file extension
   * @return file extension without dot (.) in front
   */
  const std::string getFileExtension(const std::string & filePath) const;

  std::shared_ptr<configurationserializer::DeserializeStrategy> strategy;
};

}

#endif //PRODUCTION_LINE_CONTROL_CONFIGFILE_H
