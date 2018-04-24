#include "ProductConfiguration.h"

namespace models {

    ProductConfiguration::ProductConfiguration() {
    }

    ProductConfiguration::ProductConfiguration(const ProductConfiguration &other)
            : id(other.id),
              name(other.name),
              proportion(other.proportion) {
    }

    ProductConfiguration::~ProductConfiguration() {
    }

    void ProductConfiguration::deserialize(YAML::Node &productConfigurationNode) {
        id = productConfigurationNode["id"].as<uint16_t>();
        name = productConfigurationNode["name"].as<std::string>();
        proportion = productConfigurationNode["proportion"].as<uint16_t>();
    }

    uint16_t ProductConfiguration::getId() const {
        return id;
    }

    const std::string &ProductConfiguration::getName() const {
        return name;
    }

    uint16_t ProductConfiguration::getProportion() const {
        return proportion;
    }

}