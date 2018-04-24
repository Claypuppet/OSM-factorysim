#ifndef PRODUCTION_LINE_CONTROL_PRODUCTIONLINECONFIG_H
#define PRODUCTION_LINE_CONTROL_PRODUCTIONLINECONFIG_H

#include <string>
#include <vector>
#include <cstdint>

#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/node.h>

#include "Product.h"
#include "Machine.h"

namespace Models {

    class ProductionLine {
    public:
        ProductionLine();
        ProductionLine(const ProductionLine &other);
        virtual ~ProductionLine();

        void deserialize(YAML::Node &productionLineNode);

        const std::string &getName() const;
        const std::vector<Product> &getProducts() const;
        const std::vector<Machine> &getMachines() const;

    private:
        std::string name;
        std::vector<Product> products;
        std::vector<Machine> machines;
    };

}

#endif //PRODUCTION_LINE_CONTROL_PRODUCTIONLINECONFIG_H
