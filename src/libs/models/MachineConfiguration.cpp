#include "MachineConfiguration.h"

namespace Models {

    MachineConfiguration::MachineConfiguration() {
    }

    MachineConfiguration::MachineConfiguration(const MachineConfiguration &other)
            : productId(other.productId),
              nextMachineId(other.nextMachineId),
              inputMaterialsForEachProduct(other.inputMaterialsForEachProduct),
              outputEachMinute(other.outputEachMinute),
              initializationDurationInSeconds(other.initializationDurationInSeconds),
              inputBufferSize(other.inputBufferSize),
              turnAroundTimeInSeconds(other.turnAroundTimeInSeconds),
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
            inputBufferSize = other.inputBufferSize;
            turnAroundTimeInSeconds = other.turnAroundTimeInSeconds;
            meanTimeBetweenFailureInHours = other.meanTimeBetweenFailureInHours;
            meanTimeBetweenFailureStddevInHours = other.meanTimeBetweenFailureStddevInHours;
            reparationTimeInMinutes = other.reparationTimeInMinutes;
        }

        return *this;
    }

    void MachineConfiguration::deserialize(YAML::Node &machineConfigurationConfigurationNode) {
        productId = machineConfigurationConfigurationNode["productId"].as<uint16_t>();
        nextMachineId = machineConfigurationConfigurationNode["nextMachineId"].as<uint16_t>();
        inputMaterialsForEachProduct = machineConfigurationConfigurationNode["inputMaterialsForEachProduct"].as<uint16_t>();
        outputEachMinute = machineConfigurationConfigurationNode["outputEachMinute"].as<uint16_t>();
        initializationDurationInSeconds = machineConfigurationConfigurationNode["initializationDurationInSeconds"].as<uint16_t>();
        inputBufferSize = machineConfigurationConfigurationNode["inputBufferSize"].as<uint16_t>();
        turnAroundTimeInSeconds = machineConfigurationConfigurationNode["turnAroundTimeInSeconds"].as<uint16_t>();
        meanTimeBetweenFailureInHours = machineConfigurationConfigurationNode["meanTimeBetweenFailureInHours"].as<uint16_t>();
        meanTimeBetweenFailureStddevInHours = machineConfigurationConfigurationNode["meanTimeBetweenFailureStddevInHours"].as<uint16_t>();
        reparationTimeInMinutes = machineConfigurationConfigurationNode["reparationTimeInMinutes"].as<uint16_t>();
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
        return inputBufferSize;
    }

    uint16_t MachineConfiguration::getTurnAroundTimeInSeconds() const {
        return turnAroundTimeInSeconds;
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