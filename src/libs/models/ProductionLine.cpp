#include "ProductionLine.h"

namespace models {

ProductionLine::ProductionLine(const std::string &name,
                               const std::vector<ProductPtr> &products,
                               const std::vector<MachinePtr> &machines)
    : name(name),
      products(products),
      machines(machines) {

  if (products.empty()) {
    throw std::runtime_error("ProductionLine has no products configured");
  }

  if (machines.empty()) {
    throw std::runtime_error("ProductionLine has no machines configured");
  }

}

ProductionLine::ProductionLine(const ProductionLine &other)
    : name(other.name), products(other.products), machines(other.machines) {
}

ProductionLine &ProductionLine::operator=(const ProductionLine &other) {
  if (this != &other) {
    name = other.name;
    products = other.products;
    machines = other.machines;
  }
  return *this;
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
const ProductPtr ProductionLine::getProductById(uint16_t productId) const {
  for (const auto &product : products) {
    if (product->getId() == productId) {
      return product;
    }
  }
  return nullptr;
}

}