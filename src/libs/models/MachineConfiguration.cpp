#include "MachineConfiguration.h"

namespace models {

MachineConfiguration::MachineConfiguration(uint16_t productId) : productId(productId) {

}

MachineConfiguration::MachineConfiguration(const MachineConfiguration &other)
    : productId(other.productId),
      outputEachMinute(other.outputEachMinute),
      initializationDurationInSeconds(other.initializationDurationInSeconds),
      outputBufferSize(other.outputBufferSize),
      meanTimeBetweenFailureInHours(other.meanTimeBetweenFailureInHours),
      meanTimeBetweenFailureStddevInHours(other.meanTimeBetweenFailureStddevInHours),
      reparationTimeInMinutes(other.reparationTimeInMinutes),
      previousMachines(other.previousMachines) {
}

MachineConfiguration::~MachineConfiguration() {
}

MachineConfiguration &MachineConfiguration::operator=(const MachineConfiguration &other) {
  if (this != &other) {
    productId = other.productId;
    outputEachMinute = other.outputEachMinute;
    initializationDurationInSeconds = other.initializationDurationInSeconds;
    outputBufferSize = other.outputBufferSize;
    meanTimeBetweenFailureInHours = other.meanTimeBetweenFailureInHours;
    meanTimeBetweenFailureStddevInHours = other.meanTimeBetweenFailureStddevInHours;
    reparationTimeInMinutes = other.reparationTimeInMinutes;
    previousMachines = other.previousMachines;
  }

  return *this;
}

void MachineConfiguration::deserialize(YAML::Node &machineConfigurationNode) {
  productId = machineConfigurationNode["productId"].as<uint16_t>();
  outputEachMinute = machineConfigurationNode["outputEachMinute"].as<uint16_t>();
  initializationDurationInSeconds = machineConfigurationNode["initializationDurationInSeconds"].as<uint16_t>();
  outputBufferSize = machineConfigurationNode["outputBufferSize"].as<uint16_t>();
  meanTimeBetweenFailureInHours = machineConfigurationNode["meanTimeBetweenFailureInHours"].as<uint16_t>();
  meanTimeBetweenFailureStddevInHours = machineConfigurationNode["meanTimeBetweenFailureStddevInHours"].as<uint16_t>();
  reparationTimeInMinutes = machineConfigurationNode["reparationTimeInMinutes"].as<uint16_t>();

  for (uint16_t i = 0; i < machineConfigurationNode["previousMachines"].size(); ++i) {
    previousMachines.emplace_back(PreviousMachine());
    auto previousMachineNode = machineConfigurationNode["previousMachines"][i];
    previousMachines.back().deserialize(previousMachineNode);
  }
}

uint16_t MachineConfiguration::getProductId() const {
  return productId;
}

const std::vector<PreviousMachine> &MachineConfiguration::getPreviousMachines() const {
  return previousMachines;
}

const PreviousMachine &MachineConfiguration::getPreviousMachineById(uint16_t machineId) const {
  for (const auto &machine : previousMachines) {
    if (machine.getMachineId() == machineId) {
      return machine;
    }
  }
}

uint16_t MachineConfiguration::getOutputEachMinute() const {
  return outputEachMinute;
}

uint16_t MachineConfiguration::getInitializationDurationInSeconds() const {
  return initializationDurationInSeconds;
}

uint16_t MachineConfiguration::getInitializationDurationInMilliseconds() const {
  return getInitializationDurationInSeconds() * 1000;
}

uint16_t MachineConfiguration::getOutputBufferSize() const {
  return outputBufferSize;
}

uint16_t MachineConfiguration::getMeanTimeBetweenFailureInHours() const {
  return meanTimeBetweenFailureInHours;
}

uint16_t MachineConfiguration::getMeanTimeBetweenFailureStddevInHours() const {
  return meanTimeBetweenFailureStddevInHours;
}

uint16_t MachineConfiguration::getReparationTimeInMinutes() const {
  return reparationTimeInMinutes;
}
uint16_t MachineConfiguration::getProcessTime() const {
  static const uint16_t millisecondsInMinute = 60000;
  return millisecondsInMinute / outputEachMinute;
}
void PreviousMachine::deserialize(YAML::Node &machineConfigurationNode) {
  machineId = machineConfigurationNode["machineId"].as<uint16_t>();
  neededProducts = machineConfigurationNode["neededProducts"].as<uint16_t>();
}
uint16_t PreviousMachine::getMachineId() const {
  return machineId;
}
uint16_t PreviousMachine::getNeededProducts() const {
  return neededProducts;
}
}