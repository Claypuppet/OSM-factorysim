//
// Created by don on 6-6-18.
//

#include <cereal/types/vector.hpp>
#include "MachineFinalStatistics.h"

namespace models {

MachineFinalStatistics::MachineFinalStatistics(const std::string &machineName,
                                               uint16_t machineId,
                                               uint16_t MTBFinHours,
                                               uint16_t timesBroken,
                                               uint64_t totalDownTime,
                                               const std::vector<MachineProductFinalStatistics> &productStatistics)
    : machineName(machineName),
      machineId(machineId),
      MTBFinHours(MTBFinHours),
      timesBroken(timesBroken),
      totalDownTime(totalDownTime),
      productStatistics(productStatistics) {}

const std::string &MachineFinalStatistics::getMachineName() const {
  return machineName;
}

uint16_t MachineFinalStatistics::getMachineId() const {
  return machineId;
}

uint16_t MachineFinalStatistics::getMTBFinHours() const {
  return MTBFinHours;
}

uint16_t MachineFinalStatistics::getTimesBroken() const {
  return timesBroken;
}

uint64_t MachineFinalStatistics::getTotalDownTime() const {
  return totalDownTime;
}

const std::vector<MachineProductFinalStatistics> &MachineFinalStatistics::getProductStatistics() const {
  return productStatistics;
}

}