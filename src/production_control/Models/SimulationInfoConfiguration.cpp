#include "SimulationInfoConfiguration.h"

namespace models {

    SimulationInfoConfiguration::SimulationInfoConfiguration() {
    }

    SimulationInfoConfiguration::SimulationInfoConfiguration(const SimulationInfoConfiguration &other)
            : durationInHours(other.durationInHours) {
    }

    SimulationInfoConfiguration::~SimulationInfoConfiguration() {
    }

    void SimulationInfoConfiguration::deserialize(YAML::Node &simulationInfoConfigurationNode) {
        durationInHours = simulationInfoConfigurationNode["durationInHours"].as<uint16_t>();
    }

    uint8_t SimulationInfoConfiguration::getDurationInHours() const {
        return durationInHours;
    }

}