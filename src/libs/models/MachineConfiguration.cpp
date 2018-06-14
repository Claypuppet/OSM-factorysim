#include "MachineConfiguration.h"

namespace models {

MachineConfiguration::MachineConfiguration(uint16_t productId,
                                           uint16_t outputEachMinute,
                                           const std::vector<PreviousMachinePtr> &previousMachines)
    : productId(productId),
      outputEachMinute(outputEachMinute),
      previousMachines(previousMachines) {

  if (previousMachines.empty()) {
    throw std::runtime_error("MachineConfiguration has no PreviousMachines configured");
  }
}

MachineConfiguration::MachineConfiguration(const MachineConfiguration &other)
	: productId(other.productId),
	  outputEachMinute(other.outputEachMinute),
	  previousMachines(other.previousMachines) {
}

MachineConfiguration::MachineConfiguration(uint16_t productId)
    : productId(productId) {
}

MachineConfiguration &MachineConfiguration::operator=(const MachineConfiguration &other) {
  if (this != &other) {
    productId = other.productId;
    outputEachMinute = other.outputEachMinute;
    previousMachines = other.previousMachines;
  }

  return *this;
}

uint16_t MachineConfiguration::getProductId() const {
  return productId;
}

std::vector<PreviousMachinePtr> &MachineConfiguration::getPreviousMachines() {
  return previousMachines;
}

PreviousMachinePtr MachineConfiguration::getPreviousMachineById(uint16_t machineId) const {
  for (const auto &previousMachine : previousMachines) {
	if (previousMachine->getMachineId() == machineId) {
	  return previousMachine;
	}
  }

  return nullptr;
}

uint16_t MachineConfiguration::getOutputEachMinute() const {
  return outputEachMinute;
}

uint16_t MachineConfiguration::getProcessTime() const {
  static const uint16_t millisecondsInMinute = 60000;
  return millisecondsInMinute / outputEachMinute;
}

}