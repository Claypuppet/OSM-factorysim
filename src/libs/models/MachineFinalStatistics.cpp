//
// Created by don on 6-6-18.
//

#include "MachineFinalStatistics.h"

namespace models {

MachineFinalStatistics::MachineFinalStatistics(const std::map<uint16_t, uint16_t> &avgProducedProducts,
                                               const std::map<uint16_t, uint16_t> &avgLostProducts,
                                               uint32_t avgDownTime,
                                               uint32_t avgProductionTime,
                                               uint32_t avgIdleTime,
                                               uint32_t avgConfigureTime,
                                               const std::map<uint16_t, uint16_t> &totalProducedProducts,
                                               const std::map<uint16_t, uint16_t> &totalLostProducts,
                                               uint16_t MTBF)
    : avgProducedProducts(avgProducedProducts),
      avgLostProducts(avgLostProducts),
      avgDownTime(avgDownTime),
      avgProductionTime(avgProductionTime),
      avgIdleTime(avgIdleTime),
      avgConfigureTime(avgConfigureTime),
      totalProducedProducts(totalProducedProducts),
      totalLostProducts(totalLostProducts),
      MTBFinHours(MTBF) {}

const std::map<uint16_t, uint16_t> &MachineFinalStatistics::getTotalProducedProducts() const {
  return totalProducedProducts;
}

const std::map<uint16_t, uint16_t> &MachineFinalStatistics::getTotalLostProducts() const {
  return totalLostProducts;
}

uint16_t MachineFinalStatistics::getMTBFinHours() const {
  return MTBFinHours;
}

const std::map<uint16_t, uint16_t> &MachineFinalStatistics::getAvgProducedProducts() const {
  return avgProducedProducts;
}

const std::map<uint16_t, uint16_t> &MachineFinalStatistics::getAvgLostProducts() const {
  return avgLostProducts;
}

uint32_t MachineFinalStatistics::getAvgDownTime() const {
  return avgDownTime;
}

uint32_t MachineFinalStatistics::getAvgProductionTime() const {
  return avgProductionTime;
}

uint32_t MachineFinalStatistics::getAvgIdleTime() const {
  return avgIdleTime;
}

uint32_t MachineFinalStatistics::getAvgConfigureTime() const {
  return avgConfigureTime;
}

}