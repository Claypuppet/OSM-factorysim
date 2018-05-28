#include "Machine.h"

namespace models {

Machine::Machine(uint16_t id,
                 const std::string &name,
                 const std::vector<MachineConfigurationPtr> &configurations)
    :id(id),
     name(name),
     configurations(configurations) {
}

Machine::Machine(const Machine &other)
	: id(other.id),
      name(other.name),
      configurations(other.configurations) {
}

Machine &Machine::operator=(const Machine &other) {

  if (this != &other) {
	id = other.id;
	name = other.name;
	configurations = other.configurations;
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

const MachineConfigurationPtr Machine::getConfigurationById(uint16_t machineConfigurationId) const {
  for (const auto &machineConfiugration : configurations) {
	if (machineConfiugration->getProductId() == machineConfigurationId) {
	  return machineConfiugration;
	}
  }

  return nullptr;
}

void Machine::setId(uint16_t id) {
  Machine::id = id;
}

void Machine::setName(const std::string &name) {
  Machine::name = name;
}

const MachineConfigurationPtr Machine::addConfiguration(MachineConfigurationPtr machineConfiguration) {
  configurations.emplace_back(machineConfiguration);
  return configurations.back();
}

}