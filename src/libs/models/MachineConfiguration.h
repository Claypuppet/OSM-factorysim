#ifndef PRODUCTION_LINE_CONTROL_MACHINECONFIGURATIONCONFIGURATION_H
#define PRODUCTION_LINE_CONTROL_MACHINECONFIGURATIONCONFIGURATION_H

#include <iostream> // TODO : remove line
#include <memory>

#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/node.h>
#include <cereal/cereal.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>

namespace Models {

    class MachineConfiguration;
    typedef std::shared_ptr<MachineConfiguration> MachineConfigurationPtr;

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

        template<class Archive>
        void save(Archive &ar) const
        {
            ar(productId, nextMachineId, inputMaterialsForEachProduct, outputEachMinute, initializationDurationInSeconds,
               inputBufferSize, meanTimeBetweenFailureInHours, meanTimeBetweenFailureStddevInHours, reparationTimeInMinutes);
        }

        template<class Archive>
        void load(Archive& ar)
        {
            ar(productId, nextMachineId, inputMaterialsForEachProduct, outputEachMinute, initializationDurationInSeconds,
               inputBufferSize, meanTimeBetweenFailureInHours, meanTimeBetweenFailureStddevInHours, reparationTimeInMinutes);
        }

        friend class ::cereal::access;
    };

}

#endif //PRODUCTION_LINE_CONTROL_MACHINECONFIGURATIONCONFIGURATION_H
