//
// Created by bas on 23-5-18.
//

#include "YAMLStrategy.h"

YAMLStrategy::YAMLStrategy(const YAMLStrategy& other) {
}

std::shared_ptr<models::Configuration> YAMLStrategy::deserialize(const std::string &filePath) {

  try {

    YAML::Node yamlFileNode = YAML::LoadFile(filePath);

    try {

      auto configurationModel = deserializeConfiguration(yamlFileNode);
      return configurationModel;

    } catch (const std::exception &exception) {

      std::cerr << "Configuration file incomplete: " << exception.what() << std::endl;

    }

  } catch (const std::exception &exception) {

    std::cerr << "Invalid configuration file path: " << exception.what() << std::endl;

  }
}

std::shared_ptr<models::Configuration> YAMLStrategy::deserializeConfiguration(YAML::Node &configurationYAMLNode) {
  std::string name = configurationYAMLNode["name"].as<std::string>();

  auto simulationInfoYAMLNode = configurationYAMLNode["simulationInfo"];
  auto simulationInfoModel = deserializeSimulationInfo(simulationInfoYAMLNode);

  auto productionLineYAMLNode = configurationYAMLNode["productionLine"];
  auto productionLineModel = deserializeProductionLine(productionLineYAMLNode);

  models::Configuration configurationModel(name, simulationInfoModel, productionLineModel);
  return std::make_shared<models::Configuration>(configurationModel);
}

std::shared_ptr<models::SimulationInfo> YAMLStrategy::deserializeSimulationInfo(YAML::Node &simulationInfoYAMLNode) {
  auto durationInHours = simulationInfoYAMLNode["durationInHours"].as<uint16_t>();

  models::SimulationInfo simulationInfoModel(durationInHours);
  return std::make_shared<models::SimulationInfo>(simulationInfoModel);
}

std::shared_ptr<models::ProductionLine> YAMLStrategy::deserializeProductionLine(YAML::Node &productionLineYAMLNode) {
  auto name = productionLineYAMLNode["name"].as<std::string>();

  std::vector<models::Product> productModels;
  for (uint16_t i = 0; i < productionLineYAMLNode["products"].size(); ++i) {
    auto productYAMLNode = productionLineYAMLNode["products"][i];
    auto productModel = deserializeProduct(productYAMLNode);
    productModels.emplace_back(productModel);
  }

  std::vector<models::Machine> machineModels;
  for (uint16_t i = 0; i < productionLineYAMLNode["machines"].size(); ++i) {
    auto machineYAMLNode = productionLineYAMLNode["machines"][i];
    auto machineModel = deserializeMachine(machineYAMLNode);
    machineModels.emplace_back(machineModel);
  }

  models::ProductionLine productionLineModel(name, productModels, machineModels);
  return std::make_shared<models::ProductionLine>(productionLineModel);
}

std::shared_ptr<models::Product> YAMLStrategy::deserializeProduct(YAML::Node &productYAMLNode) {
  auto id = productYAMLNode["id"].as<uint16_t>();
  auto name = productYAMLNode["name"].as<std::string>();
  auto proportion = productYAMLNode["proportion"].as<uint16_t>();

  models::Product productModel(id, name, proportion);
  return std::make_shared<models::Product>(productModel);
}

std::shared_ptr<models::Machine> YAMLStrategy::deserializeMachine(YAML::Node &machineYAMLNode) {
  auto id = machineYAMLNode["id"].as<uint16_t>();
  auto name = machineYAMLNode["name"].as<std::string>();

  std::vector<models::MachineConfiguration> configurationModels;
  for (uint16_t i = 0; i < machineYAMLNode["configurations"].size(); ++i) {
    auto machineConfigurationYAMLNode = machineYAMLNode["configurations"][i];
    auto machineConfigurationModel = deserializeMachineConfiguration(machineConfigurationYAMLNode);
    configurationModels.emplace_back(machineConfigurationModel);
  }

  models::Machine machineModel(id, name, configurationModels);
  return std::make_shared<models::Machine>(machineModel);
}

std::shared_ptr<models::MachineConfiguration> YAMLStrategy::deserializeMachineConfiguration(YAML::Node &machineConfigurationYAMLNode) {
  auto productId = machineConfigurationYAMLNode["productId"].as<uint16_t>();
  auto outputEachMinute = machineConfigurationYAMLNode["outputEachMinute"].as<uint16_t>();
  auto initializationDurationInSeconds = machineConfigurationYAMLNode["initializationDurationInSeconds"].as<uint16_t>();
  auto outputBufferSize = machineConfigurationYAMLNode["outputBufferSize"].as<uint16_t>();
  auto meanTimeBetweenFailureInHours = machineConfigurationYAMLNode["meanTimeBetweenFailureInHours"].as<uint16_t>();
  auto meanTimeBetweenFailureStddevInHours = machineConfigurationYAMLNode["meanTimeBetweenFailureStddevInHours"].as<uint16_t>();
  auto reparationTimeInMinutes = machineConfigurationYAMLNode["reparationTimeInMinutes"].as<uint16_t>();

  std::vector<models::PreviousMachine> previousMachineModels;
  for (uint16_t i = 0; i < machineConfigurationYAMLNode["previousMachines"].size(); ++i) {
    auto previousMachineYAMLNode = machineConfigurationYAMLNode["previousMachines"][i];
    auto previousMachineModel = deserializePreviousMachine(previousMachineYAMLNode);
    previousMachineModels.emplace_back(previousMachineModel);
  }

  models::MachineConfiguration machineConfigurationModel(productId,
                                                         outputEachMinute,
                                                         initializationDurationInSeconds,
                                                         outputBufferSize,
                                                         meanTimeBetweenFailureInHours,
                                                         meanTimeBetweenFailureStddevInHours,
                                                         reparationTimeInMinutes,
                                                         previousMachineModels);
  return std::make_shared<models::MachineConfiguration>(machineConfigurationModel);
}

std::shared_ptr<models::PreviousMachine> YAMLStrategy::deserializePreviousMachine(YAML::Node &previousMachineYAMLNode) {
  auto machineId = previousMachineYAMLNode["machineId"].as<uint16_t>();
  auto neededProducts = previousMachineYAMLNode["neededProducts"].as<uint16_t>();

  models::PreviousMachine previousMachineModel(machineId, neededProducts);
  return std::make_shared<models::PreviousMachine>(previousMachineModel);
}