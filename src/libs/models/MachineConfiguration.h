#ifndef PRODUCTION_LINE_CONTROL_MACHINECONFIGURATIONCONFIGURATION_H
#define PRODUCTION_LINE_CONTROL_MACHINECONFIGURATIONCONFIGURATION_H

#include <iostream> // TODO : remove line
#include <memory>

#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/node.h>
#include <cereal/cereal.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>

namespace models {

class MachineConfiguration;
typedef std::shared_ptr<MachineConfiguration> MachineConfigurationPtr;

class PreviousMachine;

class MachineConfiguration {
 public:

  /**
   * Default constructor
   */
  MachineConfiguration();
  MachineConfiguration(uint16_t productId);
  /**
   * Copy constructor
   * @param other : MachineConfiguration object to copy
   */
  MachineConfiguration(const MachineConfiguration &other);

  /**
   * The destructor
   */
  virtual ~MachineConfiguration();

  /**
   * Assignment operator
   * @param other : The MachineConfiguration object to assign
   * @return The new MachineConfiguration object
   */
  MachineConfiguration &operator=(const MachineConfiguration &other);

  /**
   * A function to deserialize a machine configuration node
   * @param machineConfigurationNode : The node to deserialize
   */
  void deserialize(YAML::Node &machineConfigurationNode);

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
   * Getter for initializationDurationInSeconds
   * @return initializationDurationInSeconds
   */
  uint16_t getInitializationDurationInSeconds() const;

  /**
   * Getter for inputBufferSize
   * @return inputBufferSize
   */
  uint16_t getOutputBufferSize() const;

  /**
   * Getter for meanTimeBetweenFailureInHours
   * @return meanTimeBetweenFailureInHours
   */
  uint16_t getMeanTimeBetweenFailureInHours() const;

  /**
   * Getter for meanTimeBetweenFailureStddevInHours
   * @return meanTimeBetweenFailureStddevInHours
   */
  uint16_t getMeanTimeBetweenFailureStddevInHours() const;

  /**
   * Getter for reparationTimeInMinutes
   * @return reparationTimeInMinutes
   */
  uint16_t getReparationTimeInMinutes() const;

  const std::vector<PreviousMachine> &getPreviousMachines() const;

 private:
  uint16_t productId;
  uint16_t outputEachMinute, initializationDurationInSeconds, outputBufferSize;
  uint16_t meanTimeBetweenFailureInHours, meanTimeBetweenFailureStddevInHours, reparationTimeInMinutes;

  std::vector<PreviousMachine> previousMachines;

  /**
   * A function to save a MachineConfiguration object in an archive
   * @tparam Archive
   * @param ar : The archive to save the object in
   */
  template<class Archive>
  void save(Archive &ar) const {
	ar(productId, outputEachMinute, initializationDurationInSeconds, previousMachines,
	   outputBufferSize, meanTimeBetweenFailureInHours, meanTimeBetweenFailureStddevInHours, reparationTimeInMinutes);
  }

  /**
   * A function to load a MachineConfiguration object from an archive
   * @tparam Archive
   * @param ar : The archive to load
   */
  template<class Archive>
  void load(Archive &ar) {
	ar(productId, outputEachMinute, initializationDurationInSeconds, previousMachines,
	   outputBufferSize, meanTimeBetweenFailureInHours, meanTimeBetweenFailureStddevInHours, reparationTimeInMinutes);
  }

  friend class ::cereal::access;

};


/**
 * Small class used by configuration to link to previous machines.
 */
class PreviousMachine {
 public:

  uint16_t getMachineId() const;
  uint16_t getNeededProducts() const;
  /**
   * A function to deserialize a machine configuration node
   * @param machineConfigurationNode : The node to deserialize
   */
  void deserialize(YAML::Node &machineConfigurationNode);

 private:
  uint16_t machineId, neededProducts;

  /**
   * A function to save a MachineConfiguration object in an archive
   * @tparam Archive
   * @param ar : The archive to save the object in
   */
  template<class Archive>
  void save(Archive &ar) const {
	ar(machineId, neededProducts);
  }

  /**
   * A function to load a MachineConfiguration object from an archive
   * @tparam Archive
   * @param ar : The archive to load
   */
  template<class Archive>
  void load(Archive &ar) {
	ar(machineId, neededProducts);
  }

  friend class ::cereal::access;
};

}

#endif //PRODUCTION_LINE_CONTROL_MACHINECONFIGURATIONCONFIGURATION_H
