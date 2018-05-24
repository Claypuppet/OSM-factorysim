#include "Configuration.h"

namespace models {

Configuration &Configuration::operator=(const Configuration &other) {
  if (this != &other) {
	this->name = other.name;
	this->simulationInfo = other.simulationInfo;
	this->productionLine = other.productionLine;
  }

  return *this;
}

const std::string &Configuration::getName() const {
  return name;
}

SimulationInfo &Configuration::getSimulationInfo() {
  return simulationInfo;
}

ProductionLine &Configuration::getProductionLine() {
  return productionLine;
}

void Configuration::setName(const std::string &name) {
  Configuration::name = name;
}

}
