#include "SimulationInfoConfiguration.h"

SimulationInfoConfiguration::SimulationInfoConfiguration(const YAML::Node& simulationInfoNode)
: durationInHours(simulationInfoNode["durationInHours"].as<uint16_t>()) {
}

SimulationInfoConfiguration::SimulationInfoConfiguration(const SimulationInfoConfiguration& other)
: durationInHours(other.durationInHours) {
}

SimulationInfoConfiguration::~SimulationInfoConfiguration() {

}