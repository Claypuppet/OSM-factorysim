//
// Created by don on 12-6-18.
//

#ifndef PRODUCTION_LINE_CONTROL_MACHINEPRODUCTFINALSTATISTICS_H
#define PRODUCTION_LINE_CONTROL_MACHINEPRODUCTFINALSTATISTICS_H

#include <stdint-gcc.h>
namespace models{

/**
 * Model that holds the final information about a machine producing this product
 */
class MachineProductFinalStatistics {
 public:
  MachineProductFinalStatistics(uint16_t id,
                                uint32_t totalProduced,
                                uint16_t avgProduced,
                                uint16_t totalLost,
                                uint16_t avgLost,
                                uint32_t avgProductionTime,
                                uint32_t avgIdleTime,
                                uint32_t avgDownTime,
                                uint32_t avgConfigureTime);
  uint16_t getId() const;
  uint32_t getTotalProduced() const;
  uint16_t getAvgProduced() const;
  uint16_t getTotalLost() const;
  uint16_t getAvgLost() const;
  uint32_t getAvgProductionTime() const;
  uint32_t getAvgIdleTime() const;
  uint32_t getAvgDownTime() const;
  uint32_t getAvgConfigureTime() const;
 private:
  uint16_t id;
  uint32_t totalProduced;
  uint16_t avgProduced;
  uint16_t totalLost;
  uint16_t avgLost;
  uint32_t avgProductionTime;
  uint32_t avgIdleTime;
  uint32_t avgDownTime;
  uint32_t avgConfigureTime;
};

}

#endif //PRODUCTION_LINE_CONTROL_MACHINEPRODUCTFINALSTATISTICS_H
