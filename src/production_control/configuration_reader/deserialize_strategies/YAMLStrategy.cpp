//
// Created by bas on 23-5-18.
//

#include "YAMLStrategy.h"

void YAMLStrategy::deserializeConfigurationFile(const std::string &filePath, models::Configuration &configuration) {
  try {
    YAML::Node yamlFileNode = YAML::LoadFile(filePath);

    try {
      deserializeConfiguration(configuration, yamlFileNode);
    } catch (const std::exception &exception) {
      std::cerr << "Configuration file incomplete: " << exception.what() << std::endl;
    }

  } catch (const std::exception &exception) {
    std::cerr << "Invalid configuration file path: " << exception.what() << std::endl;
  }
}

void YAMLStrategy::deserializeConfiguration(models::Configuration &configurationModel, YAML::Node &configurationYAMLNode) {
  std::string name = configurationYAMLNode["name"].as<std::string>();
  configurationModel.setName(name);

  auto &simulationInfoModel = configurationModel.getSimulationInfoModel();
  auto simulationInfoYAMLNode = configurationYAMLNode["simulationInfo"];
  deserializeSimulationInfo(simulationInfoModel, simulationInfoYAMLNode);

  auto &productionLineModel = configurationModel.getProductionLineModel();
  auto productionLineYAMLNode = configurationYAMLNode["productionLine"];
  deserializeProductionLine(productionLineModel, productionLineYAMLNode);
}

void YAMLStrategy::deserializeSimulationInfo(models::SimulationInfo &simulationInfoModel, YAML::Node &simulationInfoYAMLNode) {
  auto durationInHours = simulationInfoYAMLNode["durationInHours"].as<uint16_t>();
  simulationInfoModel.setDurationInHours(durationInHours);
}

void YAMLStrategy::deserializeProductionLine(models::Configuration &productionLineModel, YAML::Node &productionLineYAMLNode) {
  auto name = productionLineYAMLNode["name"].as<std::string>();
  productionLineModel.setName(name);

  for (uint16_t i = 0; i < productionLineYAMLNode["products"].size(); ++i) {
    auto productModel = productionLineModel.addProduct(models::Product());
    auto productYAMLNode = productionLineNode["products"][i];
    deserializeProduct(productModel, productYAMLNode);
  }

  for (uint16_t i = 0; i < productionLineYAMLNode["machines"].size(); ++i) {
    auto machineModel = productionLineModel.addMachine(models::Machine());
    auto machineYAMLNode = productionLineNode["machines"][i];
    deserializeMachine(machineModel, machineYAMLNode);
  }
}

void YAMLStrategy::deserializeProduct(models::Configuration &productModel, YAML::Node &productYAMLNode) {
  auto id = productYAMLNode["id"].as<uint16_t>();
  productModel.setId(id);

  auto name = productYAMLNode["name"].as<std::string>();
  productModel.setName(name);

  auto proportion = productYAMLNode["proportion"].as<uint16_t>();
  productModel.setProportion(proportion);
}

void YAMLStrategy::deserializeMachine(models::Configuration &machineModel, YAML::Node &machineYAMLNode) {
  auto id = machineYAMLNode["id"].as<uint16_t>();
  machineModel.setId(id);

  auto name = machineYAMLNode["name"].as<std::string>();
  machineModel.setName(name);

  for (uint16_t i = 0; i < machineYAMLNode["configurations"].size(); ++i) {
    auto machineConfigurationModel = machineModel.addMachineConfiguration();
    auto machineConfigurationYAMLNode = machineYAMLNode["configurations"][i];
    deserializeMachineConfiguration(machineConfigurationModel, machineConfigurationYAMLNode);
  }
}

void YAMLStrategy::deserializeMachineConfiguration(models::Configuration &machineConfigurationModel, YAML::Node &machineConfigurationYAMLNode) {
  auto productId = machineConfigurationYAMLNode["productId"].as<uint16_t>();
  machineConfigurationModel.setProductId(productId);

  auto outputEachMinute = machineConfigurationYAMLNode["outputEachMinute"].as<uint16_t>();
  machineConfigurationModel.setOutputEachMinute(outputEachMinute);

  auto initializationDurationInSeconds = machineConfigurationYAMLNode["initializationDurationInSeconds"].as<uint16_t>();
  machineConfigurationModel.setInitializationDurationInSeconds(initializationDurationInSeconds);

  auto outputBufferSize = machineConfigurationYAMLNode["outputBufferSize"].as<uint16_t>();
  machineConfigurationModel.setOutputBufferSize(outputBufferSize);

  auto meanTimeBetweenFailureInHours = machineConfigurationYAMLNode["meanTimeBetweenFailureInHours"].as<uint16_t>();
  machineConfigurationModel.setMeanTimeBetweenFailureInHours(meanTimeBetweenFailureInHours);

  auto meanTimeBetweenFailureStddevInHours = machineConfigurationYAMLNode["meanTimeBetweenFailureStddevInHours"].as<uint16_t>();
  machineConfigurationModel.setmManTimeBetweenFailureStddevInHours(meanTimeBetweenFailureStddevInHours);

  auto reparationTimeInMinutes = machineConfigurationYAMLNode["reparationTimeInMinutes"].as<uint16_t>();
  machineConfigurationModel.setReparationTimeInMinutes(reparationTimeInMinutes);

  for (uint16_t i = 0; i < machineConfigurationYAMLNode["previousMachines"].size(); ++i) {
    auto previousMachineModel = machineConfigurationModel.addPreviousMachine();
    auto previousMachineYAMLNode = machineConfigurationYAMLNode["previousMachines"][i];
    deserializePreviousMachine(previousMachineModel, previousMachineYAMLNode);
  }
}

void YAMLStrategy::deserializePreviousMachine(models::Configuration &previousMachineModel, YAML::Node &previousMachineYAMLNode) {
  auto machineId = previousMachineYAMLNode["machineId"].as<uint16_t>();
  previousMachineModel.setMachineId(machineId);

  auto neededProducts = previousMachineYAMLNode["neededProducts"].as<uint16_t>();
  previousMachineModel.setNeededProducts(neededProducts);
}