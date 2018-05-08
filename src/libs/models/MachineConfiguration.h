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
        /**
         * Default constructor
         */
        MachineConfiguration();

        /**
         * Copy constructor
         * @param other : MachineConfiguration object to copy
         */
        MachineConfiguration(const MachineConfiguration &other);

        /**
         * The destructor
         */
        virtual ~MachineConfiguration();

        /**
         * Assignment operator
         * @param other : The MachineConfiguration object to assign
         * @return The new MachineConfiguration object
         */
        MachineConfiguration& operator=(const MachineConfiguration& other);

        /**
         * A function to deserialize a machine configuration node
         * @param machineConfigurationNode : The node to deserialize
         */
        void deserialize(YAML::Node &machineConfigurationNode);

        /**
         * Getter for productId
         * @return productId
         */
        uint16_t getProductId() const;

        /**
         * Getter for nextMachineId
         * @return nextMachineId
         */
        uint16_t getNextMachineId() const;

        /**
         * Getter for inputMaterialsForEachProduct
         * @return inputMaterialsForEachProduct
         */
        uint16_t getInputMaterialsForEachProduct() const;

        /**
         * Getter for outputEachMinute
         * @return outputEachMinute
         */
        uint16_t getOutputEachMinute() const;

        /**
         * Getter for initializationDurationInSeconds
         * @return initializationDurationInSeconds
         */
        uint16_t getInitializationDurationInSeconds() const;

        /**
         * Getter for inputBufferSize
         * @return inputBufferSize
         */
        uint16_t getInputBufferSize() const;

        /**
         * Getter for meanTimeBetweenFailureInHours
         * @return meanTimeBetweenFailureInHours
         */
        uint16_t getMeanTimeBetweenFailureInHours() const;

        /**
         * Getter for meanTimeBetweenFailureStddevInHours
         * @return meanTimeBetweenFailureStddevInHours
         */
        uint16_t getMeanTimeBetweenFailureStddevInHours() const;

        /**
         * Getter for reparationTimeInMinutes
         * @return reparationTimeInMinutes
         */
        uint16_t getReparationTimeInMinutes() const;

    private:
        uint16_t productId, nextMachineId, inputMaterialsForEachProduct;
        uint16_t outputEachMinute, initializationDurationInSeconds, inputBufferSize;
        uint16_t meanTimeBetweenFailureInHours, meanTimeBetweenFailureStddevInHours, reparationTimeInMinutes;

        /**
         * A function to save a MachineConfiguration object in an archive
         * @tparam Archive
         * @param ar : The archive to save the object in
         */
        template<class Archive>
        void save(Archive &ar) const
        {
            ar(productId, nextMachineId, inputMaterialsForEachProduct, outputEachMinute, initializationDurationInSeconds,
               inputBufferSize, meanTimeBetweenFailureInHours, meanTimeBetweenFailureStddevInHours, reparationTimeInMinutes);
        }

        /**
         * A function to load a MachineConfiguration object from an archive
         * @tparam Archive
         * @param ar : The archive to load
         */
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
