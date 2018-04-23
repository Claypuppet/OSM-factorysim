//
// Created by bas on 20-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_PRODUCTCONFIGURATION_H
#define PRODUCTION_LINE_CONTROL_PRODUCTCONFIGURATION_H

#include <string>

#include <yaml-cpp/node/node.h>

class ProductConfiguration {
public:
    ProductConfiguration(const YAML::Node& productNode);
    ProductConfiguration(const ProductConfiguration& other);
    virtual ~ProductConfiguration();

private:
    uint16_t id;
    std::string name;
    uint16_t proportion;
};


#endif //PRODUCTION_LINE_CONTROL_PRODUCTCONFIGURATION_H
