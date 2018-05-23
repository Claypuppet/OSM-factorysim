#ifndef PRODUCTION_LINE_CONTROL_CONFIGFILE_H
#define PRODUCTION_LINE_CONTROL_CONFIGFILE_H

#include <string>
#include <iostream>

#include <patterns/singleton/Singleton.h>

#include "deserialize_strategies/Strategy.h"

namespace ConfigLoader {

class ConfigurationReader : public patterns::singleton::Singleton<ConfigurationReader> {
 public:
  ConfigurationReader() = default;
  ConfigurationReader(ConfigurationReader &other) = delete;
  virtual ~ConfigurationReader() = default;

  /**
   * A function that adds configuration settings into a config object
   * @param filePath : The path the config file
   * @param configuration : The configuration object
   */
  models::Configuration deserializeConfigurationFile(const std::string& filePath);

  /**
   * Get the instance, set the given strategy and return the instance.
   * @param strategy the strategy that instance has to have
   * @return instance with the given strategy
   */
  static ConfigurationReader &getInstance(Strategy strategy);

  /**
   * Set a new strategy
   * @param strategy the new strategy
   */
  void setStrategy(Strategy strategy);

 private:
  Strategy strategy;

};

}

#endif //PRODUCTION_LINE_CONTROL_CONFIGFILE_H
