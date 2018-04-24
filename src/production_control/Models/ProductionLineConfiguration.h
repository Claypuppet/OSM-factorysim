#ifndef PRODUCTION_LINE_CONTROL_PRODUCTIONLINECONFIG_H
#define PRODUCTION_LINE_CONTROL_PRODUCTIONLINECONFIG_H

#include <string>
#include <vector>
#include <cstdint>

#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/node.h>

#include "ProductConfiguration.h"
#include "MachineConfiguration.h"

namespace models {

    class ProductionLineConfiguration {
    public:
        ProductionLineConfiguration();

        ProductionLineConfiguration(const ProductionLineConfiguration &other);

        virtual ~ProductionLineConfiguration();

        void deserialize(YAML::Node &productionLineConfigurationNode);

        const std::string &getName() const;

        const std::vector<ProductConfiguration> &getProducts() const;

        const std::vector<MachineConfiguration> &getMachines() const;

    private:
        std::string name;
        std::vector<ProductConfiguration> products;
        std::vector<MachineConfiguration> machines;
    };

}

#endif //PRODUCTION_LINE_CONTROL_PRODUCTIONLINECONFIG_H
