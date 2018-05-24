#include "MachineConfiguration.h"

namespace models {

MachineConfiguration::MachineConfiguration(uint16_t productId,
                                           uint16_t outputEachMinute,
                                           uint16_t initializationDurationInSeconds,
                                           uint16_t outputBufferSize,
                                           uint16_t meanTimeBetweenFailureInHours,
                                           uint16_t meanTimeBetweenFailureStddevInHours,
                                           uint16_t reparationTimeInMinutes,
                                           const std::vector<PreviousMachine> &previousMachines)
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

const std::vector<PreviousMachine> &MachineConfiguration::getPreviousMachines() const {
  return previousMachines;
}

const PreviousMachine &MachineConfiguration::getPreviousMachineById(uint16_t machineId) const {
	// TODO : return nullptr if nothing found.
  for (const auto &previousMachine : previousMachines) {
	if (previousMachine.getMachineId() == machineId) {
	  return previousMachine;
	}
  }
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

}