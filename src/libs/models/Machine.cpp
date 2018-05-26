#include "Machine.h"

namespace models {

Machine::Machine(uint16_t id,
                 const std::string &name,
                 const std::vector<std::shared_ptr<MachineConfiguration>> &configurations)
    :id(id),
     name(name),
     configurations(configurations) {
}

Machine::Machine(const std::shared_ptr<Machine> other)
    :id(other->id),
     name(other->name),
     configurations(other->configurations) {
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

const std::vector<std::shared_ptr<MachineConfiguration>> &Machine::getConfigurations() const {
  return configurations;
}

const std::shared_ptr<MachineConfiguration> Machine::getConfigurationById(uint16_t machineConfigurationId) const {
  for (const std::shared_ptr<MachineConfiguration> machineConfiugration : configurations) {
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

const std::shared_ptr<MachineConfiguration> Machine::addConfiguration(std::shared_ptr<MachineConfiguration> machineConfiguration) {
  configurations.emplace_back(machineConfiguration);
  return configurations.back();
}

}