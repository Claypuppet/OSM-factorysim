//
// Created by bas on 23-5-18.
//

#include "PreviousMachine.h"

void PreviousMachine::deserialize(YAML::Node &machineConfigurationNode) {
  machineId = machineConfigurationNode["machineId"].as<uint16_t>();
  neededProducts = machineConfigurationNode["neededProducts"].as<uint16_t>();
}

uint16_t PreviousMachine::getMachineId() const {
  return machineId;
}

uint16_t PreviousMachine::getNeededProducts() const {
  return neededProducts;
}
