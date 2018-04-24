#ifndef PRODUCTION_LINE_CONTROL_PRODUCTCONFIGURATION_H
#define PRODUCTION_LINE_CONTROL_PRODUCTCONFIGURATION_H

#include <string>
#include <cstdint>

#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/node.h>

namespace models {

    class ProductConfiguration {
    public:
        ProductConfiguration();

        ProductConfiguration(const ProductConfiguration &other);

        virtual ~ProductConfiguration();

        void deserialize(YAML::Node &productConfigurationNode);

        uint16_t getId() const;

        const std::string &getName() const;

        uint16_t getProportion() const;

    private:
        uint16_t id;
        std::string name;
        uint16_t proportion;
    };

}

#endif //PRODUCTION_LINE_CONTROL_PRODUCTCONFIGURATION_H
