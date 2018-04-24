#ifndef PRODUCTION_LINE_CONTROL_MACHINECONFIGURATIONCONFIGURATION_H
#define PRODUCTION_LINE_CONTROL_MACHINECONFIGURATIONCONFIGURATION_H

#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/node.h>

namespace models {

    class MachineConfigurationConfiguration {
    public:
        MachineConfigurationConfiguration();

        MachineConfigurationConfiguration(const MachineConfigurationConfiguration &other);

        virtual ~MachineConfigurationConfiguration();

        void deserialize(YAML::Node &machineConfigurationConfigurationNode);

        uint16_t getProductId() const;

        uint16_t getNextMachineId() const;

        uint16_t getInputMaterialsForEachProduct() const;

        uint16_t getOutputEachMinute() const;

        uint16_t getInitializationDurationInSeconds() const;

        uint16_t getInputBufferSize() const;

        uint16_t getTurnAroundTimeInSeconds() const;

        uint16_t getMeanTimeBetweenFailureInHours() const;

        uint16_t getMeanTimeBetweenFailureStddevInHours() const;

        uint16_t getReparationTimeInMinutes() const;

    private:
        uint16_t productId, nextMachineId, inputMaterialsForEachProduct;
        uint16_t outputEachMinute, initializationDurationInSeconds, inputBufferSize;
        uint16_t turnAroundTimeInSeconds, meanTimeBetweenFailureInHours;
        uint16_t meanTimeBetweenFailureStddevInHours, reparationTimeInMinutes;
    };

}

#endif //PRODUCTION_LINE_CONTROL_MACHINECONFIGURATIONCONFIGURATION_H
