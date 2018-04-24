#ifndef PRODUCTION_LINE_CONTROL_MACHINECONFIGURATION_H
#define PRODUCTION_LINE_CONTROL_MACHINECONFIGURATION_H

#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/node.h>

#include "MachineConfigurationConfiguration.h"

namespace models {

    class MachineConfiguration {
    public:
        MachineConfiguration();

        MachineConfiguration(const MachineConfiguration &other);

        virtual ~MachineConfiguration();

        void deserialize(YAML::Node &machineConfigurationNode);

        uint16_t getId() const;

        const std::string &getName() const;

        const std::vector<MachineConfigurationConfiguration> &getConfigurations() const;

    private:
        uint16_t id;
        std::string name;
        std::vector<MachineConfigurationConfiguration> configurations;
    };

}

#endif //PRODUCTION_LINE_CONTROL_MACHINECONFIGURATION_H
