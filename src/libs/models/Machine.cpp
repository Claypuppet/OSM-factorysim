#include "Machine.h"

namespace Models {

    Machine::Machine() {
    }

    Machine::Machine(const Machine &other)
            : id(other.id),
              name(other.name) {
        for (uint16_t i = 0; i < other.configurations.size(); ++i) {
            configurations.push_back(other.configurations[i]);
        }
    }

    Machine::~Machine() {
    }

    Machine& Machine::operator=(const Machine& other) {
        if (this != &other) {
            id = other.id;
            name = other.name;

            for (uint16_t i = 0; i < other.configurations.size(); ++i) {
                configurations.push_back(other.configurations[i]);
            }
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