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
  YAMLStrategy(const YAMLStrategy& other);
  virtual ~YAMLStrategy() = default;
  
  const std::shared_ptr<models::Configuration> deserialize(const std::string &filePath) const;

 private:
  const std::shared_ptr<models::Configuration> deserializeConfiguration(YAML::Node &configurationYAMLNode) const;
  const std::shared_ptr<models::SimulationInfo> deserializeSimulationInfo(YAML::Node &simulationInfoYAMLNode) const;
  const std::shared_ptr<models::ProductionLine> deserializeProductionLine(YAML::Node &productionLineYAMLNode) const;
  const std::shared_ptr<models::Product> deserializeProduct(YAML::Node &productYAMLNode) const;
  const std::shared_ptr<models::Machine> deserializeMachine(YAML::Node &machineYAMLNode) const;
  const std::shared_ptr<models::MachineConfiguration> deserializeMachineConfiguration(YAML::Node &machineConfigurationYAMLNode) const;
  const std::shared_ptr<models::PreviousMachine> deserializePreviousMachine(YAML::Node &previousMachineYAMLNode) const;
};

#endif //PRODUCTION_LINE_CONTROL_YAMLSTRATEGY_H
