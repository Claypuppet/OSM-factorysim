//
// Created by don on 5-6-18.
//

#ifndef PRODUCTION_LINE_CONTROL_STATISTICS_H
#define PRODUCTION_LINE_CONTROL_STATISTICS_H

#include <cstdint>
#include <stdint-gcc.h>
#include <map>
#include <memory>
#include "MachineProductStatistics.h"

namespace models {

/**
 * This class is used to save weekly statistics of machines
 */
class MachineStatistics {
 public:
  MachineStatistics(uint16_t machineId, const std::vector<MachineProductStatistics> &productStatistics);
  MachineStatistics(const MachineStatistics &other);
  uint16_t getMachineId() const;
  const std::vector<MachineProductStatistics> &getProductStatistics() const;
 private:
  uint16_t machineId;
  std::vector<MachineProductStatistics> productStatistics;
};

typedef std::shared_ptr<MachineStatistics> MachineStatisticsPtr;

}

#endif //PRODUCTION_LINE_CONTROL_STATISTICS_H
