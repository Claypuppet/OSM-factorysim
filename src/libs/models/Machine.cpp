#include "Machine.h"

namespace models {

Machine::Machine(uint16_t aId, const std::string &aName)
	: id(aId), name(aName) {
}

Machine::Machine(const Machine &other)
	: id(other.id), name(other.name), configurations(other.configurations) {
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

const std::vector<MachineConfiguration> &Machine::getConfigurations() const {
  return configurations;
}
const MachineConfiguration &Machine::getConfigurationById(uint16_t configId) const {
  for (const auto &config : configurations) {
	if (config.getProductId() == configId) {
	  return config;
	}
  }
}

void Machine::setId(uint16_t id) {
  Machine::id = id;
}

void Machine::setName(const std::string &name) {
  Machine::name = name;
}

MachineConfiguration &Machine::addConfiguration(const MachineConfiguration &machineConfiguration) {
  configurations.push_back(machineConfiguration);
  return configurations.back();
}

}