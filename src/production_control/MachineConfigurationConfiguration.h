#ifndef PRODUCTION_LINE_CONTROL_MACHINECONFIGURATIONCONFIGURATION_H
#define PRODUCTION_LINE_CONTROL_MACHINECONFIGURATIONCONFIGURATION_H

#include <yaml-cpp/node/node.h>

class MachineConfigurationConfiguration {
public:
    MachineConfigurationConfiguration(const YAML::Node& machineConfigurationNode);
    MachineConfigurationConfiguration(const MachineConfigurationConfiguration& other);
    virtual ~MachineConfigurationConfiguration();

private:
    uint16_t productId, nextMachineId, inputMaterialsForEachProduct;
    uint16_t outputEachMinute, initializationDurationInSeconds, inputBufferSize;
    uint16_t turnAroundTimeInSeconds, meanTimeBetweenFailureInHours;
    uint16_t meanTimeBetweenFailureStddevInHours, reparationTimeInMinutes;
};


#endif //PRODUCTION_LINE_CONTROL_MACHINECONFIGURATIONCONFIGURATION_H
