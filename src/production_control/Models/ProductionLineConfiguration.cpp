#include "ProductionLineConfiguration.h"

namespace models {

    ProductionLineConfiguration::ProductionLineConfiguration() {
    }

    ProductionLineConfiguration::ProductionLineConfiguration(const ProductionLineConfiguration &other)
            : name(other.name) {
        for (uint16_t i = 0; i < other.products.size(); ++i) {
            products.push_back(other.products[i]);
        }

        for (uint16_t i = 0; i < other.machines.size(); ++i) {
            machines.push_back(other.machines[i]);
        }
    }

    ProductionLineConfiguration::~ProductionLineConfiguration() {
    }

    void ProductionLineConfiguration::deserialize(YAML::Node &productionLineConfigurationNode) {
        name = productionLineConfigurationNode["name"].as<std::string>();

        for (uint16_t i = 0; i < productionLineConfigurationNode["products"].size(); ++i) {
            products.push_back(ProductConfiguration());
            auto productNode = productionLineConfigurationNode["products"][i];
            products.back().deserialize(productNode);
        }

        for (uint16_t i = 0; i < productionLineConfigurationNode["machines"].size(); ++i) {
            machines.push_back(MachineConfiguration());
            auto machineNode = productionLineConfigurationNode["machines"][i];
            machines.back().deserialize(machineNode);
        }
    }

    const std::string &ProductionLineConfiguration::getName() const {
        return name;
    }

    const std::vector<ProductConfiguration> &ProductionLineConfiguration::getProducts() const {
        return products;
    }

    const std::vector<MachineConfiguration> &ProductionLineConfiguration::getMachines() const {
        return machines;
    }

}