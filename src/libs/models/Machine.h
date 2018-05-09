#ifndef PRODUCTION_LINE_CONTROL_MACHINECONFIGURATION_H
#define PRODUCTION_LINE_CONTROL_MACHINECONFIGURATION_H

// standard includes
#include <memory>
#include <string>

// library includes
#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/node.h>
#include <cereal/cereal.hpp>
#include <cstdint>

// other includes
#include "MachineConfiguration.h"

namespace models {

class Machine;
typedef std::shared_ptr<Machine> MachinePtr;

class Machine {
 public:
  /**
   * Default constructor
   */
  Machine() = default;

  /**
   * A constructor
   * @param aId : Id of the machine
   * @param aName : Name of the machine
   */
  Machine(uint16_t aId, std::string aName);

  /**
   * Copy constructor
   * @param other : The Machine to copy
   */
  Machine(const Machine &other);

  /**
   * The destructor
   */
  virtual ~Machine();

  /**
   * Asignment operator
   * @param other : The Machine object to assign
   * @return The new Machine object
   */
  Machine &operator=(const Machine &other);

  /**
   * A function to deserialize a machine node
   * @param machineNode : The node to deserialize
   */
  void deserialize(YAML::Node &machineNode);

  /**
  * Getter for id
  * @return id
  */
  uint16_t getId() const;

  /**
   * Getter for name
   * @return name
   */
  const std::string &getName() const;

  /**
   * Getter for configurations
   * @return configurations
   */
  const std::vector<MachineConfiguration> &getConfigurations() const;

 protected:
  uint16_t id;
  std::string name;
  std::vector<MachineConfiguration> configurations;

 private:

  /**
   * A function to save the object in an archive
   * @tparam Archive
   * @param ar : The archive to save the object in
   */
  template<class Archive>
  void save(Archive &ar) const {
    ar(id, name, configurations);
  }

  /**
   * A function to load a machine object from an archive
   * @tparam Archive
   * @param ar : The archive to load
   */
  template<class Archive>
  void load(Archive &ar) {
    ar(id, name, configurations);
  };

  friend class ::cereal::access;
};

}

#endif //PRODUCTION_LINE_CONTROL_MACHINECONFIGURATION_H
