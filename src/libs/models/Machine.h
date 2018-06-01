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

/**
 * Class that deserializes and hold information about a machine
 */
class Machine {
 public:

  /**
   * Enum of all machine states
   */
  enum MachineStatus {
	kMachineStatusInitializing,       // 0
	kMachineStatusConfiguring,        // 1
	kMachineStatusIdle,               // 2
	kMachineStatusProcessingProduct,  // 3
    kMachineStatusDisconnected,       // 4
	kMachineStatusBroken,             // 5
  };

  /**
   * Enum of all machine error codes
   */
  enum MachineErrorCode {
    kMachineErrorCodeBroke
  };

  /**
   * Enum of result log ids
   */
  enum MachineLogEventIds {
    kMachineLogEventMachineStatusUpdate,
    kMachineLogEventMachineReconfigured,
    kMachineLogEventMachineBufferUpdate,
  };

  Machine() = default;
  virtual ~Machine() = default;

  /**
   * ...
   * @param id
   * @param name
   * @param configurations
   */
  Machine(uint16_t id,
          const std::string &name = "",
          const std::vector<MachineConfigurationPtr> &configurations = std::vector<MachineConfigurationPtr>());

  /**
   * Copy this class
   * @param other const ref to other class
   */
  Machine(const Machine &other);

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
  const std::vector<MachineConfigurationPtr> &getConfigurations() const;

  /**
   * Cehcks if machine has configuration
   * @param configurationId
   * @return : true if machine has given configuration
   */
  bool hasConfiguration(uint16_t configurationId) const;

  /**
   * Get machine configuration of this machine by id
   * @param configId id of the config
   * @return machine configuration of this machine with the given id
   */
  const MachineConfigurationPtr getConfigurationById(uint16_t machineConfigurationId) const;

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
  const MachineConfigurationPtr addConfiguration(MachineConfigurationPtr machineConfiguration);

 protected:
  uint16_t id;
  std::string name;
  std::vector<MachineConfigurationPtr> configurations;

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

typedef std::shared_ptr<Machine> MachinePtr;

}

#endif //PRODUCTION_LINE_CONTROL_MACHINECONFIGURATION_H
