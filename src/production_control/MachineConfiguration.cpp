#include "MachineConfiguration.h"

MachineConfiguration::MachineConfiguration(const YAML::Node& machineNode)
: id(machineNode["id"].as<uint16_t>()),
  name(machineNode["name"].as<std::string>()) {
    for (uint8_t i = 0; i < machineNode["configurations"].size(); ++i) {
        YAML::Node machineConfigurationsNode = machineNode["configurations"][i];
        configurations.push_back(MachineConfigurationConfiguration(machineConfigurationsNode));
    }
}

MachineConfiguration::MachineConfiguration(const MachineConfiguration& other)
: id(other.id),
  name(other.name),
  configurations(other.configurations) {
}

MachineConfiguration::~MachineConfiguration() {
}