
#include "YAMLStrategy.h"

namespace configurationserializer {

YAMLStrategy::YAMLStrategy(const YAMLStrategy &other) {
}

const std::shared_ptr<models::Configuration> YAMLStrategy::deserialize(const std::string &filePath) const {

  try {

    YAML::Node yamlFileNode = YAML::LoadFile(filePath);
    return deserializeConfiguration(yamlFileNode);

  } catch (const YAML::Exception &exception) {

    std::cerr << "YAML Exception: " << exception.what() << std::endl;
    throw exception;

  } catch (const std::exception &exception) {

    std::cerr << exception.what() << std::endl;
    throw exception;

  }
}

const std::shared_ptr<models::Configuration> YAMLStrategy::deserializeConfiguration(YAML::Node &configurationYAMLNode) const {
  const auto name = configurationYAMLNode["name"].as<std::string>();

  YAML::Node simulationInfoYAMLNode = configurationYAMLNode["simulationInfo"];
  const auto simulationInfoModel = deserializeSimulationInfo(simulationInfoYAMLNode);

  YAML::Node productionLineYAMLNode = configurationYAMLNode["productionLine"];
  const auto productionLineModel = deserializeProductionLine(productionLineYAMLNode);

  return std::make_shared<models::Configuration>(name, simulationInfoModel, productionLineModel);
}

const std::shared_ptr<models::SimulationInfo> YAMLStrategy::deserializeSimulationInfo(YAML::Node &simulationInfoYAMLNode) const {
  auto durationInHours = simulationInfoYAMLNode["durationInHours"].as<uint16_t>();
  auto startHourOfWorkDay = simulationInfoYAMLNode["startHourOfWorkDay"].as<uint16_t>();
  auto workDayDurationInHours = simulationInfoYAMLNode["workDayDurationInHours"].as<uint16_t>();

  return std::make_shared<models::SimulationInfo>(durationInHours, startHourOfWorkDay, workDayDurationInHours);
}

const std::shared_ptr<models::ProductionLine> YAMLStrategy::deserializeProductionLine(YAML::Node &productionLineYAMLNode) const {
  const auto name = productionLineYAMLNode["name"].as<std::string>();

  std::vector<std::shared_ptr<models::Product>> productModels;
  for (uint16_t i = 0; i < productionLineYAMLNode["products"].size(); ++i) {
    YAML::Node productYAMLNode = productionLineYAMLNode["products"][i];
    const std::shared_ptr<models::Product> productModel = deserializeProduct(productYAMLNode);
    productModels.emplace_back(productModel);
  }

  std::vector<std::shared_ptr<models::Machine>> machineModels;
  for (uint16_t i = 0; i < productionLineYAMLNode["machines"].size(); ++i) {
    YAML::Node machineYAMLNode = productionLineYAMLNode["machines"][i];
    const std::shared_ptr<models::Machine> machineModel = deserializeMachine(machineYAMLNode);
    machineModels.emplace_back(machineModel);
  }

  return std::make_shared<models::ProductionLine>(name, productModels, machineModels);
}

const std::shared_ptr<models::Product> YAMLStrategy::deserializeProduct(YAML::Node &productYAMLNode) const {
  auto id = productYAMLNode["id"].as<uint16_t>();
  auto name = productYAMLNode["name"].as<std::string>();
  auto proportion = productYAMLNode["proportion"].as<uint16_t>();

  return std::make_shared<models::Product>(id, name, proportion);
}

const std::shared_ptr<models::Machine> YAMLStrategy::deserializeMachine(YAML::Node &machineYAMLNode) const {
  auto id = machineYAMLNode["id"].as<uint16_t>();
  auto name = machineYAMLNode["name"].as<std::string>();
  auto initializationDurationInSeconds = machineYAMLNode["initializationDurationInSeconds"].as<uint16_t>();
  auto meanTimeBetweenFailureInHours = machineYAMLNode["meanTimeBetweenFailureInHours"].as<uint16_t>();
  auto reparationTimeInMinutes = machineYAMLNode["reparationTimeInMinutes"].as<uint16_t>();
  auto reparationTimeStddevInMinutes = machineYAMLNode["reparationTimeStddevInMinutes"].as<uint16_t>();

  YAML::Node postProcesInfoYAMLNode = machineYAMLNode["postProcessInfo"];
  const models::PostProcessInfoPtr postProcessInfo = deserializePostProcesInfo(postProcesInfoYAMLNode);

  std::vector<models::MachineConfigurationPtr> configurationModels;
  for (uint16_t i = 0; i < machineYAMLNode["configurations"].size(); ++i) {
    YAML::Node machineConfigurationYAMLNode = machineYAMLNode["configurations"][i];
    const auto machineConfigurationModel = deserializeMachineConfiguration(machineConfigurationYAMLNode);
    configurationModels.emplace_back(machineConfigurationModel);
  }

  return std::make_shared<models::Machine>(id,
                                           meanTimeBetweenFailureInHours,
                                           reparationTimeInMinutes,
                                           reparationTimeStddevInMinutes,
                                           initializationDurationInSeconds,
                                           postProcessInfo,
                                           name,
                                           configurationModels);
}

const std::shared_ptr<models::PostProcessInfo> YAMLStrategy::deserializePostProcesInfo(YAML::Node &postProcesInfoYAMLNode) const {
  if(postProcesInfoYAMLNode.IsMap()){
    auto inputDelayInSeconds = postProcesInfoYAMLNode["inputDelayInSeconds"].as<uint16_t>();;
    auto postProcessDurationInMinutes = postProcesInfoYAMLNode["postProcessDurationInMinutes"].as<uint16_t>();;

    return std::make_shared<models::PostProcessInfo>(inputDelayInSeconds, postProcessDurationInMinutes);
  }
  return std::shared_ptr<models::PostProcessInfo>();
}

const std::shared_ptr<models::MachineConfiguration> YAMLStrategy::deserializeMachineConfiguration(YAML::Node &machineConfigurationYAMLNode) const {
  auto productId = machineConfigurationYAMLNode["productId"].as<uint16_t>();
  auto outputEachMinute = machineConfigurationYAMLNode["outputEachMinute"].as<uint16_t>();

  std::vector<std::shared_ptr<models::PreviousMachine>> previousMachineModels;
  for (uint16_t i = 0; i < machineConfigurationYAMLNode["previousMachines"].size(); ++i) {
    YAML::Node previousMachineYAMLNode = machineConfigurationYAMLNode["previousMachines"][i];
    std::shared_ptr<models::PreviousMachine> previousMachineModel = deserializePreviousMachine(previousMachineYAMLNode);
    previousMachineModels.emplace_back(previousMachineModel);
  }

  return std::make_shared<models::MachineConfiguration>(productId,
                                                        outputEachMinute,
                                                        previousMachineModels);
}

const std::shared_ptr<models::PreviousMachine> YAMLStrategy::deserializePreviousMachine(YAML::Node &previousMachineYAMLNode) const {
  auto machineId = previousMachineYAMLNode["machineId"].as<uint16_t>();
  auto neededProducts = previousMachineYAMLNode["neededProducts"].as<uint16_t>();
  auto inputBufferSize = previousMachineYAMLNode["inputBufferSize"].as<uint16_t>();

  return std::make_shared<models::PreviousMachine>(machineId, neededProducts, inputBufferSize);
}

}