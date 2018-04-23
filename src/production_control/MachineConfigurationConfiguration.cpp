#include "MachineConfigurationConfiguration.h"

MachineConfigurationConfiguration::MachineConfigurationConfiguration(const YAML::Node& machineConfigurationNode)
: productId(machineConfigurationNode["productId"].as<uint16_t>()),
  nextMachineId(machineConfigurationNode["nextMachineId"].as<uint16_t>()),
  inputMaterialsForEachProduct(machineConfigurationNode["inputMaterialsForEachProduct"].as<uint16_t>()),
  outputEachMinute(machineConfigurationNode["outputEachMinute"].as<uint16_t>()),
  initializationDurationInSeconds(machineConfigurationNode["initializationDurationInSeconds"].as<uint16_t>()),
  inputBufferSize(machineConfigurationNode["inputBufferSize"].as<uint16_t>()),
  turnAroundTimeInSeconds(machineConfigurationNode["turnAroundTimeInSeconds"].as<uint16_t>()),
  meanTimeBetweenFailureInHours(machineConfigurationNode["meanTimeBetweenFailureInHours"].as<uint16_t>()),
  meanTimeBetweenFailureStddevInHours(machineConfigurationNode["meanTimeBetweenFailureStddevInHours"].as<uint16_t>()),
  reparationTimeInMinutes(machineConfigurationNode["reparationTimeInMinutes"].as<uint16_t>()) {
}

MachineConfigurationConfiguration::MachineConfigurationConfiguration(const MachineConfigurationConfiguration& other)
: productId(other.productId),
  nextMachineId(other.nextMachineId),
  inputMaterialsForEachProduct(other.inputMaterialsForEachProduct),
  outputEachMinute(other.outputEachMinute),
  initializationDurationInSeconds(other.initializationDurationInSeconds),
  inputBufferSize(other.inputBufferSize),
  turnAroundTimeInSeconds(other.turnAroundTimeInSeconds),
  meanTimeBetweenFailureInHours(other.meanTimeBetweenFailureInHours),
  meanTimeBetweenFailureStddevInHours(other.meanTimeBetweenFailureStddevInHours),
  reparationTimeInMinutes(other.reparationTimeInMinutes) {
}

MachineConfigurationConfiguration::~MachineConfigurationConfiguration() {
}
