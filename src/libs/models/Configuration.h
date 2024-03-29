
// All specializations of shared_ptr meet the requirements of CopyConstructible, CopyAssignable, and LessThanComparable and are contextually convertible to bool.

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

/**
 * Model class holds all information about a simulation
 * Name of the simulation
 * The production line that is used
 * Information about the simulation
 */
class Configuration;
typedef std::shared_ptr<Configuration> ConfigurationPtr;

class Configuration {
 public:

  Configuration() = default;
  /**
   * Default destructor
   */
  virtual ~Configuration() = default;

  /**
   * ...
   * @param name
   * @param simulationInfo
   * @param productionLine
   */
  Configuration(const std::string &name,
                const SimulationInfoPtr &simulationInfo,
                const ProductionLinePtr &productionLine);

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
  const SimulationInfoPtr getSimulationInfo() const;
  const ProductionLinePtr getProductionLine() const;

  // NORMAL SETTERS
  void setName(const std::string &name);

 private:
  std::string name;
  SimulationInfoPtr simulationInfo;
  ProductionLinePtr productionLine;

  /**
   * Function to serialize class from archive
   * @tparam Archive
   * @param ar : The archive to load
   */
  template<class Archive>
  void serialize(Archive &ar) {
    ar(name,
       simulationInfo,
       productionLine);
  }

  friend class ::cereal::access;
};

}

#endif //PRODUCTION_LINE_CONTROL_CONFIG_H
