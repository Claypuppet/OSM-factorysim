#ifndef PRODUCTION_LINE_CONTROL_CONFIGFILE_H
#define PRODUCTION_LINE_CONTROL_CONFIGFILE_H

#include <string>
#include <iostream>

#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/node.h>

#include <patterns/singleton/Singleton.h>

#include <models/Configuration.h>

namespace ConfigLoader {

class ConfigurationReader : public patterns::singleton::Singleton<ConfigurationReader> {
 public:
  /**
   * Default constructor
   */
  ConfigurationReader();

  ConfigurationReader(ConfigurationReader &other) = delete;

  /**
   * The destructor
   */
  virtual ~ConfigurationReader();

  /**
   * A function that adds configuration settings into a config object
   * @param filePath : The path the config file
   * @param configuration : The configuration object
   */
  void readConfigurationFile(std::string filePath, models::Configuration &configuration);
};

}

#endif //PRODUCTION_LINE_CONTROL_CONFIGFILE_H
