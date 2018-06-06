//
// Created by don on 6-6-18.
//

#ifndef PRODUCTION_LINE_CONTROL_MACHINEFINALSTATISTICS_H
#define PRODUCTION_LINE_CONTROL_MACHINEFINALSTATISTICS_H

#include "MachineStatistics.h"

namespace models {

class MachineFinalStatistics : public MachineStatistics {
 public:
  MachineFinalStatistics(const std::map<uint16_t, uint16_t> &producedProducts,
                         const std::map<uint16_t, uint16_t> &lostProducts,
                         uint32_t downTime,
                         uint32_t productionTime,
                         uint32_t idleTime,
                         uint32_t configureTime,
                         uint32_t totalProducedProducts,
                         uint32_t totalLostProducts,
                         uint16_t MTBF);
 private:
 public:
  uint32_t getTotalProducedProducts() const;
  uint32_t getTotalLostProducts() const;
  uint16_t getMTBF() const;
 private:
  uint32_t totalProducedProducts;
  uint32_t totalLostProducts;
  uint16_t MTBF;
};

}

#endif //PRODUCTION_LINE_CONTROL_MACHINEFINALSTATISTICS_H
