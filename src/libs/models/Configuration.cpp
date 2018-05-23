#include "Configuration.h"

namespace models {

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

SimulationInfo &Configuration::getSimulationInfoModel() const {
  return simulationInfo;
}

ProductionLine &Configuration::getProductionLineModel() const {
  return productionLine;
}

void Configuration::setName(const std::string &name) {
  Configuration::name = name;
}

}
