#include "ProductionLine.h"

namespace models {

ProductionLine::ProductionLine(const std::string &name,
							   const std::vector<ProductPtr> &products,
							   const std::vector<MachinePtr> &machines)
		: name(name),
		  products(products),
		  machines(machines) {

	if (products.size() == 0) {
		throw std::runtime_error("ProductionLine has no products configured");
	}

	if (machines.size() == 0) {
		throw std::runtime_error("ProductionLine has no machines configured");
	}

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

const std::string &ProductionLine::getName() const {
  return name;
}

const std::vector<ProductPtr> &ProductionLine::getProducts() const {
  return products;
}

const std::vector<MachinePtr> &ProductionLine::getMachines() const {
  return machines;
}

}