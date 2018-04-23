//
// Created by bas on 20-4-18.
//

#include "ProductConfiguration.h"

ProductConfiguration::ProductConfiguration(const YAML::Node& productNode)
: id(productNode["id"].as<uint16_t>()),
  name(productNode["name"].as<std::string>()),
  proportion(productNode["proportion"].as<uint16_t>()) {
}

ProductConfiguration::ProductConfiguration(const ProductConfiguration& other) {

}

ProductConfiguration::~ProductConfiguration() {

}