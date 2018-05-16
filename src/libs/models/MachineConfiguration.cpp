#include "MachineConfiguration.h"

namespace models {

    MachineConfiguration::MachineConfiguration() {
    }

    MachineConfiguration::MachineConfiguration(const MachineConfiguration &other)
            : productId(other.productId),
              nextMachineId(other.nextMachineId),
              inputMaterialsForEachProduct(other.inputMaterialsForEachProduct),
              outputEachMinute(other.outputEachMinute),
              initializationDurationInSeconds(other.initializationDurationInSeconds),
              outputBufferSize(other.outputBufferSize),
              meanTimeBetweenFailureInHours(other.meanTimeBetweenFailureInHours),
              meanTimeBetweenFailureStddevInHours(other.meanTimeBetweenFailureStddevInHours),
              reparationTimeInMinutes(other.reparationTimeInMinutes) {
    }

    MachineConfiguration::~MachineConfiguration() {
    }

    MachineConfiguration& MachineConfiguration::operator=(const MachineConfiguration& other) {
        if (this != &other) {
            productId = other.productId;
            nextMachineId = other.nextMachineId;
            inputMaterialsForEachProduct = other.inputMaterialsForEachProduct;
            outputEachMinute = other.outputEachMinute;
            initializationDurationInSeconds = other.initializationDurationInSeconds;
            outputBufferSize = other.outputBufferSize;
            meanTimeBetweenFailureInHours = other.meanTimeBetweenFailureInHours;
            meanTimeBetweenFailureStddevInHours = other.meanTimeBetweenFailureStddevInHours;
            reparationTimeInMinutes = other.reparationTimeInMinutes;
        }

        return *this;
    }

    void MachineConfiguration::deserialize(YAML::Node &machineConfigurationNode) {
        productId = machineConfigurationNode["productId"].as<uint16_t>();
        nextMachineId = machineConfigurationNode["nextMachineId"].as<uint16_t>();
        inputMaterialsForEachProduct = machineConfigurationNode["inputMaterialsForEachProduct"].as<uint16_t>();
        outputEachMinute = machineConfigurationNode["outputEachMinute"].as<uint16_t>();
        initializationDurationInSeconds = machineConfigurationNode["initializationDurationInSeconds"].as<uint16_t>();
        outputBufferSize = machineConfigurationNode["outputBufferSize"].as<uint16_t>();
        meanTimeBetweenFailureInHours = machineConfigurationNode["meanTimeBetweenFailureInHours"].as<uint16_t>();
        meanTimeBetweenFailureStddevInHours = machineConfigurationNode["meanTimeBetweenFailureStddevInHours"].as<uint16_t>();
        reparationTimeInMinutes = machineConfigurationNode["reparationTimeInMinutes"].as<uint16_t>();
    }

    uint16_t MachineConfiguration::getProductId() const {
        return productId;
    }

    uint16_t MachineConfiguration::getNextMachineId() const {
        return nextMachineId;
    }

    uint16_t MachineConfiguration::getInputMaterialsForEachProduct() const {
        return inputMaterialsForEachProduct;
    }

    uint16_t MachineConfiguration::getOutputEachMinute() const {
        return outputEachMinute;
    }

    uint16_t MachineConfiguration::getInitializationDurationInSeconds() const {
        return initializationDurationInSeconds;
    }

    uint16_t MachineConfiguration::getInputBufferSize() const {
        return outputBufferSize;
    }

    uint16_t MachineConfiguration::getMeanTimeBetweenFailureInHours() const {
        return meanTimeBetweenFailureInHours;
    }

    uint16_t MachineConfiguration::getMeanTimeBetweenFailureStddevInHours() const {
        return meanTimeBetweenFailureStddevInHours;
    }

    uint16_t MachineConfiguration::getReparationTimeInMinutes() const {
        return reparationTimeInMinutes;
    }

}