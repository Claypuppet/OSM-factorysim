#include "MachineConfigurationConfiguration.h"

namespace models {

    MachineConfigurationConfiguration::MachineConfigurationConfiguration() {
    }

    MachineConfigurationConfiguration::MachineConfigurationConfiguration(const MachineConfigurationConfiguration &other)
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

    MachineConfigurationConfiguration::~MachineConfigurationConfiguration() {
    }

    void MachineConfigurationConfiguration::deserialize(YAML::Node &machineConfigurationConfigurationNode) {
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

    uint16_t MachineConfigurationConfiguration::getProductId() const {
        return productId;
    }

    uint16_t MachineConfigurationConfiguration::getNextMachineId() const {
        return nextMachineId;
    }

    uint16_t MachineConfigurationConfiguration::getInputMaterialsForEachProduct() const {
        return inputMaterialsForEachProduct;
    }

    uint16_t MachineConfigurationConfiguration::getOutputEachMinute() const {
        return outputEachMinute;
    }

    uint16_t MachineConfigurationConfiguration::getInitializationDurationInSeconds() const {
        return initializationDurationInSeconds;
    }

    uint16_t MachineConfigurationConfiguration::getInputBufferSize() const {
        return inputBufferSize;
    }

    uint16_t MachineConfigurationConfiguration::getTurnAroundTimeInSeconds() const {
        return turnAroundTimeInSeconds;
    }

    uint16_t MachineConfigurationConfiguration::getMeanTimeBetweenFailureInHours() const {
        return meanTimeBetweenFailureInHours;
    }

    uint16_t MachineConfigurationConfiguration::getMeanTimeBetweenFailureStddevInHours() const {
        return meanTimeBetweenFailureStddevInHours;
    }

    uint16_t MachineConfigurationConfiguration::getReparationTimeInMinutes() const {
        return reparationTimeInMinutes;
    }

}