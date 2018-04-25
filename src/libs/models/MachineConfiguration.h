#ifndef PRODUCTION_LINE_CONTROL_MACHINECONFIGURATIONCONFIGURATION_H
#define PRODUCTION_LINE_CONTROL_MACHINECONFIGURATIONCONFIGURATION_H

#include <iostream> // TODO : remove line

#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/node.h>

namespace Models {

    class MachineConfiguration {
    public:
        MachineConfiguration();
        MachineConfiguration(const MachineConfiguration &other);
        virtual ~MachineConfiguration();

        MachineConfiguration& operator=(const MachineConfiguration& other);

        void deserialize(YAML::Node &machineConfigurationNode);

        uint16_t getProductId() const;
        uint16_t getNextMachineId() const;
        uint16_t getInputMaterialsForEachProduct() const;
        uint16_t getOutputEachMinute() const;
        uint16_t getInitializationDurationInSeconds() const;
        uint16_t getInputBufferSize() const;
        uint16_t getMeanTimeBetweenFailureInHours() const;
        uint16_t getMeanTimeBetweenFailureStddevInHours() const;
        uint16_t getReparationTimeInMinutes() const;

    private:
        uint16_t productId, nextMachineId, inputMaterialsForEachProduct;
        uint16_t outputEachMinute, initializationDurationInSeconds, inputBufferSize;
        uint16_t meanTimeBetweenFailureInHours, meanTimeBetweenFailureStddevInHours, reparationTimeInMinutes;
    };

}

#endif //PRODUCTION_LINE_CONTROL_MACHINECONFIGURATIONCONFIGURATION_H
