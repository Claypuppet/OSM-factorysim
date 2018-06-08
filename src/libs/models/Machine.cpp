#include "Machine.h"

namespace models {

Machine::Machine(uint16_t id,
                 uint16_t meanTimeBetweenFailureInHours,
                 uint16_t reparationTimeInMinutes,
                 uint16_t reparationTimeStddevInMinutes,
                 uint16_t initializationDurationInSeconds,
                 const PostProcessInfoPtr &postProcesInfo,
                 const std::string &name,
                 const std::vector<MachineConfigurationPtr> &configurations)
    :id(id),
     name(name),
     meanTimeBetweenFailureInHours(meanTimeBetweenFailureInHours),
     reparationTimeInMinutes(reparationTimeInMinutes),
     reparationTimeStddevInMinutes(reparationTimeStddevInMinutes),
     initializationDurationInSeconds(initializationDurationInSeconds),
     configurations(configurations),
     postProcessInfo(postProcesInfo){

  if (configurations.empty()) {
    throw std::runtime_error("Machine has no configurations configured");
  }

}

Machine::Machine(const Machine &other)
    :id(other.id),
     name(other.name),
     meanTimeBetweenFailureInHours(other.meanTimeBetweenFailureInHours),
     reparationTimeInMinutes(other.reparationTimeInMinutes),
     reparationTimeStddevInMinutes(other.reparationTimeStddevInMinutes),
     initializationDurationInSeconds(other.initializationDurationInSeconds),
     configurations(other.configurations),
     postProcessInfo(other.postProcessInfo) {
}

Machine &Machine::operator=(const Machine &other) {

  if (this != &other) {
	id = other.id;
	name = other.name;
	meanTimeBetweenFailureInHours = other.meanTimeBetweenFailureInHours;
	reparationTimeInMinutes = other.reparationTimeInMinutes;
	reparationTimeStddevInMinutes = other.reparationTimeStddevInMinutes;
	initializationDurationInSeconds = other.initializationDurationInSeconds;
    configurations = other.configurations;
    postProcessInfo = other.postProcessInfo;
  }

  return *this;
}

uint16_t Machine::getId() const {
  return id;
}

const std::string &Machine::getName() const {
  return name;
}

const std::vector<MachineConfigurationPtr> &Machine::getConfigurations() const {
  return configurations;
}

bool Machine::hasConfiguration(uint16_t machineConfigurationId) const {
  for (const auto &machineConfiugration : configurations) {
    if (machineConfiugration->getProductId() == machineConfigurationId) {
      return true;
    }
  }
  return false;
}

const MachineConfigurationPtr Machine::getConfigurationById(uint16_t machineConfigurationId) const {
  for (const auto &machineConfiugration : configurations) {
	if (machineConfiugration->getProductId() == machineConfigurationId) {
	  return machineConfiugration;
	}
  }

  return nullptr;
}

uint16_t Machine::getMeanTimeBetweenFailureInHours() const {
  return meanTimeBetweenFailureInHours;
}

uint32_t Machine::getMeanTimeBetweenFailureInMillis() const {
  return 3600000u * meanTimeBetweenFailureInHours;
}

uint16_t Machine::getReparationTimeInMinutes() const {
  return reparationTimeInMinutes;
}

uint32_t Machine::getReparationTimeInMillis() const {
  return 60000u * reparationTimeInMinutes;
}

uint16_t Machine::getReparationTimeStddevInMinutes() const {
  return reparationTimeStddevInMinutes;
}

uint16_t Machine::getInitializationDurationInSeconds() const {
  return initializationDurationInSeconds;
}

uint32_t Machine::getInitializationDurationInMilliseconds() const {
  return 1000u * initializationDurationInSeconds;
}

const std::shared_ptr<PostProcessInfo> Machine::getPostProcessInfo() const {
  return postProcessInfo;
}

}