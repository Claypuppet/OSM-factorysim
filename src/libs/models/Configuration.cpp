#include "Configuration.h"

namespace models {

Configuration::Configuration(const std::string &name,
                             std::shared_ptr<SimulationInfo> simulationInfo,
                             std::shared_ptr<ProductionLine> productionLine)
    : name(name),
      simulationInfo(simulationInfo),
      productionLine(productionLine) {
}

Configuration::Configuration(const Configuration &other)
    : name(other.name),
      simulationInfo(other.simulationInfo),
      productionLine(other.productionLine) {
}

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

const std::shared_ptr<SimulationInfo> Configuration::getSimulationInfo() const {
  return simulationInfo;
}

const std::shared_ptr<ProductionLine> Configuration::getProductionLine() const {
  return productionLine;
}

void Configuration::setName(const std::string &name) {
  Configuration::name = name;
}

}
