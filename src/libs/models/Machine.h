#ifndef PRODUCTION_LINE_CONTROL_MACHINECONFIGURATION_H
#define PRODUCTION_LINE_CONTROL_MACHINECONFIGURATION_H

#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/node.h>

#include "MachineConfiguration.h"

namespace Models {

    class Machine {
    public:
        Machine();

        Machine(const Machine &other);

        virtual ~Machine();

        void deserialize(YAML::Node &machineNode);

        uint16_t getId() const;
        const std::string &getName() const;
        const std::vector<MachineConfiguration> &getConfigurations() const;

    private:
        uint16_t id;
        std::string name;
        std::vector<MachineConfiguration> configurations;
    };

}

#endif //PRODUCTION_LINE_CONTROL_MACHINECONFIGURATION_H
