//
// Created by don on 12-6-18.
//

#ifndef PRODUCTION_LINE_CONTROL_MACHINEPRODUCTSTATISTICS_H
#define PRODUCTION_LINE_CONTROL_MACHINEPRODUCTSTATISTICS_H

#include <cstdint>

namespace models {

/**
 * Model that holds information about a machine producing this product
 */
class MachineProductStatistics {
 public:
  MachineProductStatistics(uint16_t productId,
                           uint32_t productionTime,
                           uint32_t downTime,
                           uint32_t idleTime,
                           uint32_t configureTime,
                           uint16_t produced,
                           uint16_t lost);
  uint16_t getProductId() const;
  uint32_t getProductionTime() const;
  uint32_t getDownTime() const;
  uint32_t getIdleTime() const;
  uint32_t getConfigureTime() const;
  uint16_t getProduced() const;
  uint16_t getLost() const;
 private:
  uint16_t productId;
  uint32_t productionTime;
  uint32_t downTime;
  uint32_t idleTime;
  uint32_t configureTime;
  uint16_t produced;
  uint16_t lost;
};

}

#endif //PRODUCTION_LINE_CONTROL_MACHINEPRODUCTSTATISTICS_H
