//
// Created by don on 6-6-18.
//

#ifndef PRODUCTION_LINE_CONTROL_MACHINEFINALSTATISTICS_H
#define PRODUCTION_LINE_CONTROL_MACHINEFINALSTATISTICS_H

#include <cstdint>
#include <map>
#include <memory>

namespace models {

/**
 * Model that holds all statistics of a machine for a completed simulation
 */
class MachineFinalStatistics{
 public:
  MachineFinalStatistics(uint16_t machinedId,
                         const std::string &machineName,
                         const std::map<uint16_t, uint16_t> &avgProducedProducts,
                         const std::map<uint16_t, uint16_t> &avgLostProducts,
                         uint32_t avgDownTime,
                         uint32_t avgProductionTime,
                         uint32_t avgIdleTime,
                         uint32_t avgConfigureTime,
                         const std::map<uint16_t, uint32_t> &totalProducedProducts,
                         const std::map<uint16_t, uint32_t> &totalLostProducts,
                         uint16_t timesBroken,
                         uint16_t MTBF);
  const std::map<uint16_t, uint32_t> &getTotalProducedProducts() const;
  const std::map<uint16_t, uint32_t> &getTotalLostProducts() const;
  const std::map<uint16_t, uint16_t> &getAvgProducedProducts() const;
  const std::map<uint16_t, uint16_t> &getAvgLostProducts() const;
  uint32_t getAvgDownTime() const;
  uint32_t getAvgProductionTime() const;
  uint32_t getAvgIdleTime() const;
  uint32_t getAvgConfigureTime() const;
  uint16_t getMTBFinHours() const;
  uint16_t getMachineId() const;
  const std::string &getMachineName() const;
  uint16_t getTimesBroken() const;
 private:
  uint16_t machineId;
  std::string machineName;
  std::map<uint16_t, uint16_t> avgProducedProducts;
  std::map<uint16_t, uint16_t> avgLostProducts;
  uint32_t avgDownTime;
  uint32_t avgProductionTime;
  uint32_t avgIdleTime;
  uint32_t avgConfigureTime;
  std::map<uint16_t, uint32_t> totalProducedProducts;
  std::map<uint16_t, uint32_t> totalLostProducts;
  uint16_t timesBroken;
  uint16_t MTBFinHours;
};

typedef std::shared_ptr<MachineFinalStatistics> MachineFinalStatisticsPtr;

}

#endif //PRODUCTION_LINE_CONTROL_MACHINEFINALSTATISTICS_H
