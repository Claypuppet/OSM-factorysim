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

  void deserializeConfigurationFile(const std::string &filePath, models::Configuration &configuration);

 private:
  void deserializeConfiguration(models::Configuration &configurationModel, YAML::Node &configurationYAMLNode);
  void deserializeSimulationInfo(models::SimulationInfo &simulationInfoModel, YAML::Node &simulationInfoYAMLNode);
  void deserializeProductionLine(models::Configuration &productionLineModel, YAML::Node &productionLineYAMLNode);
  void deserializeProduct(models::Configuration &productModel, YAML::Node &productYAMLNode);
  void deserializeMachine(models::Configuration &machineModel, YAML::Node &machineYAMLNode);
  void deserializeMachineConfiguration(models::Configuration &machineConfigurationModel, YAML::Node &machineConfigurationYAMLNode);
  void deserializePreviousMachine(models::Configuration &previousMachineModel, YAML::Node &previousMachineYAMLNode);
};

#endif //PRODUCTION_LINE_CONTROL_YAMLSTRATEGY_H
