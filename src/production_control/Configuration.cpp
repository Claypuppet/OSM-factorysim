#include "Configuration.h"

Configuration::Configuration(const YAML::Node& configurationNode)
: name(configurationNode["name"].as<std::string>()),
  simulationInfoConfiguration(configurationNode["simulationInfo"]),
  productionLineConfiguration(configurationNode["productionLine"])  {
}

Configuration::Configuration(const Configuration& other)
: name(other.name),
  simulationInfoConfiguration(other.simulationInfoConfiguration),
  productionLineConfiguration(other.productionLineConfiguration) {
}

Configuration::~Configuration() {
}
