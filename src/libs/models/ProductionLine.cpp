#include "ProductionLine.h"

namespace models {

ProductionLine::ProductionLine() {
}

ProductionLine::ProductionLine(const ProductionLine &other)
	: name(other.name) {
  for (uint16_t i = 0; i < other.products.size(); ++i) {
	products.push_back(other.products[i]);
  }

  for (uint16_t i = 0; i < other.machines.size(); ++i) {
	machines.push_back(other.machines[i]);
  }
}

ProductionLine::~ProductionLine() {
}

ProductionLine &ProductionLine::operator=(const ProductionLine &other) {
  if (this != &other) {
	name = other.name;

	for (uint16_t i = 0; i < other.products.size(); ++i) {
	  products.push_back(other.products[i]);
	}

	for (uint16_t i = 0; i < other.machines.size(); ++i) {
	  machines.push_back(other.machines[i]);
	}
  }
}

void ProductionLine::deserialize(YAML::Node &productionLineNode) {
  name = productionLineNode["name"].as<std::string>();

  for (uint16_t i = 0; i < productionLineNode["products"].size(); ++i) {
	products.push_back(Product());
	auto productNode = productionLineNode["products"][i];
	products.back().deserialize(productNode);
  }

  for (uint16_t i = 0; i < productionLineNode["machines"].size(); ++i) {
	machines.push_back(Machine());
	auto machineNode = productionLineNode["machines"][i];
	machines.back().deserialize(machineNode);
  }
}

const std::string &ProductionLine::getName() const {
  return name;
}

const std::vector<Product> &ProductionLine::getProducts() const {
  return products;
}

const std::vector<Machine> &ProductionLine::getMachines() const {
  return machines;
}

}