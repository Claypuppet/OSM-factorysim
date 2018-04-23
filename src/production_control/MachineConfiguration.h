#ifndef PRODUCTION_LINE_CONTROL_MACHINECONFIGURATION_H
#define PRODUCTION_LINE_CONTROL_MACHINECONFIGURATION_H

#include <string>
#include <vector>

#include <yaml-cpp/node/node.h>

#include "MachineConfigurationConfiguration.h"

class MachineConfiguration {
public:
    MachineConfiguration(const YAML::Node& machineNode);
    MachineConfiguration(const MachineConfiguration& other);
    virtual ~MachineConfiguration();

private:
    uint16_t id;
    std::string name;
    std::vector<MachineConfigurationConfiguration> configurations;
};

#endif //PRODUCTION_LINE_CONTROL_MACHINECONFIGURATION_H
