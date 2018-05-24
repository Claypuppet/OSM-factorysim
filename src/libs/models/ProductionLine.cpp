#include "ProductionLine.h"

namespace models {

ProductionLine::ProductionLine(const std::string &name,
							   const std::vector<Product> &products,
							   const std::vector<Machine> &machines)
		: name(name),
		  products(products),
		  machines(machines) {
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

const std::vector<Product> &ProductionLine::getProducts() const {
  return products;
}

const std::vector<Machine> &ProductionLine::getMachines() const {
  return machines;
}

}