#include "MachineConfiguration.h"

namespace models {

    MachineConfiguration::MachineConfiguration() {
    }

    MachineConfiguration::MachineConfiguration(const MachineConfiguration &other)
            : id(other.id),
              name(other.name) {
        for (uint16_t i = 0; i < other.configurations.size(); ++i) {
            configurations.push_back(other.configurations[i]);
        }
    }

    MachineConfiguration::~MachineConfiguration() {
    }

    void MachineConfiguration::deserialize(YAML::Node &machineConfigurationNode) {
        id = machineConfigurationNode["id"].as<uint16_t>();
        name = machineConfigurationNode["name"].as<std::string>();

        for (uint16_t i = 0; i < machineConfigurationNode["configurations"].size(); ++i) {
            configurations.push_back(MachineConfigurationConfiguration());
            auto machineConfigurationConfigurationNode = machineConfigurationNode["configurations"][i];
            configurations.back().deserialize(machineConfigurationConfigurationNode);
        }
    }

    uint16_t MachineConfiguration::getId() const {
        return id;
    }

    const std::string &MachineConfiguration::getName() const {
        return name;
    }

    const std::vector<MachineConfigurationConfiguration> &MachineConfiguration::getConfigurations() const {
        return configurations;
    }

}