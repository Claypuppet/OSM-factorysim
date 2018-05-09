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

void Machine::deserialize(YAML::Node &machineNode) {
  id = machineNode["id"].as<uint16_t>();
  name = machineNode["name"].as<std::string>();

  for (uint16_t i = 0; i < machineNode["configurations"].size(); ++i) {
    configurations.push_back(MachineConfiguration());
    auto machineConfigurationNode = machineNode["configurations"][i];
    configurations.back().deserialize(machineConfigurationNode);
  }
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

}