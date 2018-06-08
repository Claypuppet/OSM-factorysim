//
// Created by don on 5-6-18.
//

#ifndef PRODUCTION_LINE_CONTROL_STATISTICS_H
#define PRODUCTION_LINE_CONTROL_STATISTICS_H

#include <cstdint>
#include <stdint-gcc.h>
#include <map>
#include <memory>

namespace models {

/**
 * This class is used to save weekly statistics of machines
 */
class MachineStatistics {
 public:
  MachineStatistics(uint16_t machineId,
                    const std::map<uint16_t, uint16_t> &producedProducts,
                    const std::map<uint16_t, uint16_t> &lostProducts,
                    uint32_t downTime,
                    uint32_t productionTime,
                    uint32_t idleTime,
                    uint32_t configureTime);
  const std::map<uint16_t, uint16_t> &getProducedProducts() const;
  const std::map<uint16_t, uint16_t> &getLostProducts() const;
  uint32_t getDownTime() const;
  uint32_t getProductionTime() const;
  uint32_t getIdleTime() const;
  uint32_t getConfigureTime() const;
  uint16_t getMachineId() const;
  void setMachineId(uint16_t machineId);
 private:
  uint16_t machineId;
  /**
   * product_id, amount of produced products
   */
  std::map<uint16_t, uint16_t> producedProducts;
  /**
   * product_id, amount of lost products
   */
  std::map<uint16_t, uint16_t> lostProducts;
  uint32_t downTime;
  uint32_t productionTime;
  uint32_t idleTime;
  uint32_t configureTime;
};

typedef std::shared_ptr<MachineStatistics> MachineStatisticsPtr;

}

#endif //PRODUCTION_LINE_CONTROL_STATISTICS_H
