#ifndef PRODUCTION_LINE_CONTROL_CONFIGFILE_H
#define PRODUCTION_LINE_CONTROL_CONFIGFILE_H

#include <string>
#include <iostream>

#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/node.h>

#include <patterns/singleton/Singleton.h>

#include "Configuration.h"

namespace models {

    class ConfigurationReader : public Patterns::Singleton::Singleton<ConfigurationReader> {
    public:
        ConfigurationReader();

        ConfigurationReader(ConfigurationReader &other) = delete;

        virtual ~ConfigurationReader();

        void readConfigurationFile(std::string filePath, Configuration &configuration);
    };

}

#endif //PRODUCTION_LINE_CONTROL_CONFIGFILE_H
