#ifndef PRODUCTION_LINE_CONTROL_PRODUCTCONFIGURATION_H
#define PRODUCTION_LINE_CONTROL_PRODUCTCONFIGURATION_H

#include <string>
#include <cstdint>

#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/node.h>

namespace Models {

    class Product {
    public:
        Product();
        Product(const Product &other);
        virtual ~Product();

        void deserialize(YAML::Node &productNode);

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
