#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONINFOCONFIG_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONINFOCONFIG_H

// standard library includes
#include <memory>

// library includes
#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/node.h>
#include <cereal/cereal.hpp>

// other includes
// -

namespace models {

class SimulationInfo;
typedef std::shared_ptr<SimulationInfo> SimulationInfoPtr;

class SimulationInfo {
 public:
  /**
   * Default constructor
   */
  SimulationInfo();

  /**
   * Copy constructor
   * @param other : The object to copy
   */
  SimulationInfo(const SimulationInfo &other);

  /**
   * The destructor
   */
  virtual ~SimulationInfo();

  /**
   * Assignment operator
   * @param other : The object to assign
   * @return The new object
   */
  SimulationInfo &operator=(const SimulationInfo &other);

  /**
   * A function to deserialize a simulation info node
   * @param simulationInfoNode : The node to deserialize
   */
  void deserialize(YAML::Node &simulationInfoNode);

  /**
   * Getter for durationInHours
   * @return durationInHours
   */
  uint8_t getDurationInHours() const;

 private:
  uint8_t durationInHours;

  /**
   * A function to save a SimulationInfo object in an archive
   * @tparam Archive
   * @param ar : The archive to save the object in
   */
  template<class Archive>
  void save(Archive &ar) const {
	ar(durationInHours);
  }

  /**
   * A function to load a SimulationInfo object from an archive
   * @tparam Archive
   * @param ar : The archive to load
   */
  template<class Archive>
  void load(Archive &ar) {
	ar(durationInHours);
  }

  friend class cereal::access;
};

}

#endif //PRODUCTION_LINE_CONTROL_SIMULATIONINFOCONFIG_H
