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
   * Enum of all machine states
   */
  enum MachineStatus {
	kMachineStatusWaitingForConfig,
	kMachineStatusConfiguring,
	kMachineStatusSelftesting,
	kMachineStatusIdle,
	kMachineStatusTakingProduct,
	kMachineStatusProcessingProduct,
	kMachineStatusTakingOutProduct,
	kMachineStatusBroken,
	kMachineStatusRepairing,
  };

  /**
   * Copy this class
   * @param other const ref to other class
   */
  Machine(const Machine &other);

  /**
   * Default destructor
   */
  virtual ~Machine() = default;

  /**
   * Assign a object to this object
   * @param other other object of this class
   * @return this object
   */
  Machine &operator=(const Machine &other);

  /**
   * Get id of this machine
   * @return id of this machine
   */
  uint16_t getId() const;

  /**
   * Get the name of this machine
   * @return name of this machine
   */
  const std::string &getName() const;

  /**
   * Get vector of machine configurations
   * @return vector with all machines configurations of this machine
   */
  const std::vector<MachineConfiguration> &getConfigurations() const;

  /**
   * Get machine configuration of this machine by id
   * @param configId id of the config
   * @return machine configuration of this machine with the given id
   */
  const MachineConfiguration &getConfigurationById(uint16_t configId) const;

  /**
   * Set the machine id
   * @param id the new machine id
   */
  void setId(uint16_t id);

  /**
   * Set the machine name
   * @param name the new machine name
   */
  void setName(const std::string &name);

  /**
   * Add a machine configuration to this machine
   * @param machineConfiguration machine configuration model
   * @return the new machine configuration
   */
  MachineConfiguration &addConfiguration(const MachineConfiguration &machineConfiguration);

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
  void save(Archive &archive) const {
    archive(id, name, configurations);
  }

  /**
   * A function to load a machine object from an archive
   * @tparam Archive
   * @param ar : The archive to load
   */
  template<class Archive>
  void load(Archive &archive) {
    archive(id, name, configurations);
  };

  friend class ::cereal::access;
};

}

#endif //PRODUCTION_LINE_CONTROL_MACHINECONFIGURATION_H
