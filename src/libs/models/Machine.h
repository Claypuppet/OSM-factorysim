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
  Machine() = default;

  /**
   * A constructor
   * @param aId : Id of the machine
   * @param aName : Name of the machine
   */
  Machine(uint16_t aId, const std::string &aName = "");
  Machine(const Machine &other);

  virtual ~Machine() = default;

  Machine &operator=(const Machine &other);

  /**
   * A function to deserialize a machine node
   * @param machineNode : The node to deserialize
   */
  void deserialize(YAML::Node &machineNode);

  uint16_t getId() const;
  const std::string &getName() const;
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
