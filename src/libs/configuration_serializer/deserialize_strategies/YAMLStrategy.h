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

#include "DeserializeStrategy.h"

namespace configurationserializer {

/**
 * Class to deserialize YAML configuration files.
 */
class YAMLStrategy : public DeserializeStrategy {
 public:
  YAMLStrategy() = default;
  YAMLStrategy(const YAMLStrategy &other);
  virtual ~YAMLStrategy() = default;

  const std::shared_ptr<models::Configuration> deserialize(const std::string &filePath) const;

 private:

  /**
   * Deserialize a configuration node
   * @param configurationYAMLNode node with all information that configuration needs
   * @return shared pointer to the formatted configuration object
   */
  const std::shared_ptr<models::Configuration> deserializeConfiguration(YAML::Node &configurationYAMLNode) const;

  /**
   * Deserialize a simulationInfo node
   * @param simulationInfoYAMLNode node with all information that simulationInfo needs
   * @return shared pointer to the formatted simulationInfo object
   */
  const std::shared_ptr<models::SimulationInfo> deserializeSimulationInfo(YAML::Node &simulationInfoYAMLNode) const;

  /**
   * Deserialize a productionLine node
   * @param productionLineYAMLNode node with all information that productionLine needs
   * @return shared pointer to the formatted productionLine object
   */
  const std::shared_ptr<models::ProductionLine> deserializeProductionLine(YAML::Node &productionLineYAMLNode) const;

  /**
   * Deserialize a product node
   * @param productYAMLNode node with all information that product needs
   * @return shared pointer to the formatted product object
   */
  const std::shared_ptr<models::Product> deserializeProduct(YAML::Node &productYAMLNode) const;

  /**
   * Deserialize a machine node
   * @param productionLineYAMLNode node with all information that machine needs
   * @return shared pointer to the formatted machine object
   */
  const std::shared_ptr<models::Machine> deserializeMachine(YAML::Node &machineYAMLNode) const;

  /**
   * Deserilize a postProcesInfo node
   * @param postProcesInfoYAMLNode node with all information that postProcesInfo needs
   * @return shared pointer to the formatted post proces info
   */
  const std::shared_ptr<models::PostProcessInfo> deserializePostProcesInfo(YAML::Node &postProcesInfoYAMLNode) const;

  /**
   * Deserialize a machineConfiguration node
   * @param machineConfigurationYAMLNode node with all information that machineConfiguration needs
   * @return shared pointer to the formatted machineConfiguration object
   */
  const std::shared_ptr<models::MachineConfiguration> deserializeMachineConfiguration(YAML::Node &machineConfigurationYAMLNode) const;

  /**
   * Deserialize a previousMachine node
   * @param machineConfigurationYAMLNode node with all information that previousMachine needs
   * @return shared pointer to the formatted previousMachine object
   */
  const std::shared_ptr<models::PreviousMachine> deserializePreviousMachine(YAML::Node &previousMachineYAMLNode) const;
};

}

#endif //PRODUCTION_LINE_CONTROL_YAMLSTRATEGY_H
