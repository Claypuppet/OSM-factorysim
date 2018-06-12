//
// Created by don on 6-6-18.
//

#ifndef PRODUCTION_LINE_CONTROL_MACHINEFINALSTATISTICS_H
#define PRODUCTION_LINE_CONTROL_MACHINEFINALSTATISTICS_H

#include <cstdint>
#include <map>
#include <memory>
#include "MachineProductFinalStatistics.h"

namespace models {

/**
 * Model that holds all statistics of a machine for a completed simulation
 */
class MachineFinalStatistics {
 public:
  MachineFinalStatistics(const std::string &machineName,
                         uint16_t machineId,
                         uint16_t MTBFinHours,
                         uint16_t timesBroken,
                         uint64_t totalDownTime,
                         const std::vector<MachineProductFinalStatistics> &productStatistics);
  const std::string &getMachineName() const;
  uint16_t getMachineId() const;
  uint16_t getMTBFinHours() const;
  uint16_t getTimesBroken() const;
  uint64_t getTotalDownTime() const;
  const std::vector<MachineProductFinalStatistics> &getProductStatistics() const;
 private:
  std::string machineName;
  uint16_t machineId;
  uint16_t MTBFinHours;
  uint16_t timesBroken;
  uint64_t totalDownTime;
  std::vector<models::MachineProductFinalStatistics> productStatistics;
};

typedef std::shared_ptr<MachineFinalStatistics> MachineFinalStatisticsPtr;

}

#endif //PRODUCTION_LINE_CONTROL_MACHINEFINALSTATISTICS_H
