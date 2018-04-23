
#ifndef PRODUCTION_LINE_CONTROL_PRODUCTIONLINECONFIG_H
#define PRODUCTION_LINE_CONTROL_PRODUCTIONLINECONFIG_H

#include <string>
#include <vector>

#include <yaml-cpp/node/node.h>

#include "ProductConfiguration.h"
#include "MachineConfiguration.h"

class ProductionLineConfiguration {
public:
    ProductionLineConfiguration(const YAML::Node& productionLineConfigurationNode);
    ProductionLineConfiguration(const ProductionLineConfiguration& other);
    virtual ~ProductionLineConfiguration();

private:
    std::string name;
    std::vector<ProductConfiguration> products;
    std::vector<MachineConfiguration> machines;
};


#endif //PRODUCTION_LINE_CONTROL_PRODUCTIONLINECONFIG_H
