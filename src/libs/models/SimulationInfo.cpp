#include "SimulationInfo.h"

namespace models {

SimulationInfo::SimulationInfo(const SimulationInfo &other)
	: durationInHours(other.durationInHours) {
}

SimulationInfo &SimulationInfo::operator=(const SimulationInfo &other) {
  if (this != &other) {
	durationInHours = other.durationInHours;
  }

  return *this;
}

void SimulationInfo::deserialize(YAML::Node &simulationInfoNode) {
  durationInHours = simulationInfoNode["durationInHours"].as<uint16_t>();
}

uint8_t SimulationInfo::getDurationInHours() const {
  return durationInHours;
}

}