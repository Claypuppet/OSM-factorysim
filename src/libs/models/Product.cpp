#include "Product.h"

namespace models {

Product::Product() {
}

Product::Product(const Product &other)
	: id(other.id),
	  name(other.name),
	  proportion(other.proportion) {
}

Product::~Product() {
}

Product &Product::operator=(const Product &other) {
  if (this != &other) {
	id = other.id;
	name = other.name;
	proportion = other.proportion;
  }

  return *this;
}

void Product::deserialize(YAML::Node &productNode) {
  id = productNode["id"].as<uint16_t>();
  name = productNode["name"].as<std::string>();
  proportion = productNode["proportion"].as<uint16_t>();
}

uint16_t Product::getId() const {
  return id;
}

const std::string &Product::getName() const {
  return name;
}

uint16_t Product::getProportion() const {
  return proportion;
}

}