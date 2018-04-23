#ifndef PRODUCTION_LINE_CONTROL_CONFIGFILE_H
#define PRODUCTION_LINE_CONTROL_CONFIGFILE_H

#include <string>
#include <iostream>

#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>
#include <yaml-cpp/yaml.h>
#include <patterns/Singleton.h>

#include "Configuration.h"

class ConfigurationReader : public Singleton {
public:
    ConfigurationReader(const std::string& newFilePath);
    ConfigurationReader(const ConfigurationReader& other);
    virtual ~ConfigurationReader();
    void readFile(const std::string& newFilePath);

private:
    std::string filePath;
    Configuration configuration;
};

#endif //PRODUCTION_LINE_CONTROL_CONFIGFILE_H
