#include "MachineConfiguration.h"

namespace models {

MachineConfiguration::MachineConfiguration(uint16_t productId,
                                           uint16_t outputEachMinute,
                                           uint16_t initializationDurationInSeconds,
                                           uint16_t outputBufferSize,
                                           uint16_t meanTimeBetweenFailureInHours,
                                           uint16_t meanTimeBetweenFailureStddevInHours,
                                           uint16_t reparationTimeInMinutes,
                                           const std::vector<PreviousMachinePtr> &previousMachines)
    : productId(productId),
      outputEachMinute(outputEachMinute),
      initializationDurationInSeconds(initializationDurationInSeconds),
      outputBufferSize(outputBufferSize),
      meanTimeBetweenFailureInHours(meanTimeBetweenFailureInHours),
      meanTimeBetweenFailureStddevInHours(meanTimeBetweenFailureStddevInHours),
      reparationTimeInMinutes(reparationTimeInMinutes),
      previousMachines(previousMachines) {
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

MachineConfiguration::MachineConfiguration(uint16_t productId)
    : productId(productId) {
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

uint16_t MachineConfiguration::getInitializationDurationInSeconds() const {
  return initializationDurationInSeconds;
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

}