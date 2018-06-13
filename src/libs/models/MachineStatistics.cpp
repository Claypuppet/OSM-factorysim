//
// Created by don on 5-6-18.
//

#include <cereal/types/vector.hpp>
#include "MachineStatistics.h"

namespace models {

MachineStatistics::MachineStatistics(uint16_t machineId, const std::vector<MachineProductStatistics> &productStatistics)
    : machineId(machineId), productStatistics(productStatistics) {}

uint16_t MachineStatistics::getMachineId() const {
  return machineId;
}

const std::vector<MachineProductStatistics> &MachineStatistics::getProductStatistics() const {
  return productStatistics;
}

}