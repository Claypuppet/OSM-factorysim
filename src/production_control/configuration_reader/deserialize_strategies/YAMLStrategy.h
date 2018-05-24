//
// Created by bas on 23-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_YAMLSTRATEGY_H
#define PRODUCTION_LINE_CONTROL_YAMLSTRATEGY_H

#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/node.h>

#include <models/Configuration.h>
#include <models/SimulationInfo.h>
#include <models/ProductionLine.h>
#include <models/Product.h>
#include <models/Machine.h>
#include <models/MachineConfiguration.h>

#include "Strategy.h"

class YAMLStrategy : public Strategy {
public:
  YAMLStrategy() = default;
  YAMLStrategy(const YAMLStrategy& other) = delete;
  virtual ~YAMLStrategy() = default;

  std::shared_ptr<models::Configuration> deserialize(const std::string &filePath);

 private:
  std::shared_ptr<models::Configuration> deserializeConfiguration(YAML::Node &configurationYAMLNode);
  std::shared_ptr<models::SimulationInfo> deserializeSimulationInfo(YAML::Node &simulationInfoYAMLNode);
  std::shared_ptr<models::ProductionLine> deserializeProductionLine(YAML::Node &productionLineYAMLNode);
  std::shared_ptr<models::Product> deserializeProduct(YAML::Node &productYAMLNode);
  std::shared_ptr<models::Machine> deserializeMachine(YAML::Node &machineYAMLNode);
  std::shared_ptr<models::MachineConfiguration> deserializeMachineConfiguration(YAML::Node &machineConfigurationYAMLNode);
  std::shared_ptr<models::PreviousMachine> deserializePreviousMachine(YAML::Node &previousMachineYAMLNode);
};

#endif //PRODUCTION_LINE_CONTROL_YAMLSTRATEGY_H
