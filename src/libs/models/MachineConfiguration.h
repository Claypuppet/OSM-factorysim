#ifndef PRODUCTION_LINE_CONTROL_MACHINECONFIGURATIONCONFIGURATION_H
#define PRODUCTION_LINE_CONTROL_MACHINECONFIGURATIONCONFIGURATION_H

#include <iostream> // TODO : remove line
#include <memory>

#include <cereal/cereal.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>

#include "PreviousMachine.h"

namespace models {

/**
 * Machines use the class to hold information about their configurations
 */
class MachineConfiguration {
 public:
  MachineConfiguration() = default;

  /**
   * Construct a new MachineConfiguration object
   * @param productId id of the product that this configuration creates
   * @param outputEachMinute production each minute
   * @param previousMachines all previous machines of this machine configuration
   */
  MachineConfiguration(uint16_t productId,
                       uint16_t outputEachMinute,
                       const std::vector<PreviousMachinePtr> &previousMachines);

  /**
   * Destruct the object
   */
  virtual ~MachineConfiguration() = default;

  /**
   * Construct a sample MachineConfiguration
   * - Used in unittests
   * @param productId
   */
  MachineConfiguration(uint16_t productId);

  /**
   * Copy the machine configuration object
   * @param other : other MachineConfiguration object
   */
  MachineConfiguration(const MachineConfiguration &other);

  /**
   * Assignment operator
   * @param other : The MachineConfiguration object to assign
   * @return The new MachineConfiguration object
   */
  MachineConfiguration &operator=(const MachineConfiguration &other);

  /**
   * Getter for productId
   * @return productId
   */
  uint16_t getProductId() const;

  /**
   * Getter for outputEachMinute
   * @return outputEachMinute
   */
  uint16_t getOutputEachMinute() const;

  /**
   * Calculate the time needed to product one product
   * @return process time in milliseconds
   */
  uint16_t getProcessTime() const;

  /**
   * Get all previous machines of this configuration
   * @return a vector with the previous machines of this configuration
   */
  std::vector<PreviousMachinePtr> &getPreviousMachines();

  /**
   * Get previous machine by id
   * @param machineId id of the previous machine you want to get
   * @return the model of the previous machine (if found)
   */
  PreviousMachinePtr getPreviousMachineById(uint16_t machineId) const;

 private:
  uint16_t productId;
  uint16_t outputEachMinute;
  std::vector<PreviousMachinePtr> previousMachines;

  /**
   * A function to serialize a MachineConfiguration object from an archive
   * @tparam Archive
   * @param ar : The archive to load
   */
  template<class Archive>
  void serialize(Archive &ar) {
	ar(productId,
       outputEachMinute,
       previousMachines);
  }

  friend class ::cereal::access;
};

typedef std::shared_ptr<MachineConfiguration> MachineConfigurationPtr;

}

#endif //PRODUCTION_LINE_CONTROL_MACHINECONFIGURATIONCONFIGURATION_H
