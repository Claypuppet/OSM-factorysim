//
// Created by don on 5-6-18.
//

#ifndef PRODUCTION_LINE_CONTROL_STATISTICS_H
#define PRODUCTION_LINE_CONTROL_STATISTICS_H

#include <cstdint>
#include <stdint-gcc.h>

namespace models {

/**
 * This class is used to save weekly statistics of machines
 */
class MachineStatistics {
 public:
  MachineStatistics(uint16_t producedProducts,
                    uint16_t lostProducts,
                    uint32_t downTime,
                    uint32_t productionTime,
                    uint32_t idleTime,
                    uint32_t configureTime);
  uint16_t getProducedProducts() const;
  uint16_t getLostProducts() const;
  uint32_t getDownTime() const;
  uint32_t getProductionTime() const;
  uint32_t getIdleTime() const;
  uint32_t getConfigureTime() const;
 private:
  uint16_t producedProducts;
  uint16_t lostProducts;
  uint32_t downTime;
  uint32_t productionTime;
  uint32_t idleTime;
  uint32_t configureTime;
};

}

#endif //PRODUCTION_LINE_CONTROL_STATISTICS_H
