#ifndef PRODUCTION_LINE_CONTROL_CONFIG_H
#define PRODUCTION_LINE_CONTROL_CONFIG_H

#include <string>
#include <memory>

#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/node.h>
#include <cereal/cereal.hpp>

#include "SimulationInfo.h"
#include "ProductionLine.h"

namespace models {

class Configuration;
typedef std::shared_ptr<Configuration> ConfigurationPtr;

class Configuration {
 public:

  /**
   * construct a empty Configuration object
   */
  Configuration() = default;

  /**
   * Default destructor
   */
  virtual ~Configuration() = default;

  /**
   * Copy constructor
   * @param other : Configuration object to copy
   */
  Configuration(const Configuration &other);

  /**
   * Asignment operator
   * @param other : other Configuration object
   * @return new Configuration object
   */
  Configuration &operator=(const Configuration &other);

  // NORMAL GETTERS
  const std::string &getName() const;
  SimulationInfo &getSimulationInfo();
  ProductionLine &getProductionLine();

  // NORMAL SETTERS
  void setName(const std::string &name);

 private:
  std::string name;
  SimulationInfo simulationInfo;
  ProductionLine productionLine;

  /**
   * Function to save class as archive
   * @tparam Archive
   * @param ar : Archive to store class in
   */
  template<class Archive>
  void save(Archive &ar) const {
	ar(name, simulationInfo, productionLine);
  }

  /**
   * Function to load class from archive
   * @tparam Archive
   * @param ar : The archive to load
   */
  template<class Archive>
  void load(Archive &ar) {
	ar(name, simulationInfo, productionLine);
  }

  friend class ::cereal::access;
};

}

#endif //PRODUCTION_LINE_CONTROL_CONFIG_H
