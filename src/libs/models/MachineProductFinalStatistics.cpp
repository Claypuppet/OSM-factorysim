//
// Created by don on 12-6-18.
//

#include "MachineProductFinalStatistics.h"

namespace models {

models::MachineProductFinalStatistics::MachineProductFinalStatistics(uint16_t id,
                                                                     uint32_t totalProduced,
                                                                     uint16_t avgProduced,
                                                                     uint16_t totalLost,
                                                                     uint16_t avgLost,
                                                                     uint32_t avgProductionTime,
                                                                     uint32_t avgIdleTime,
                                                                     uint32_t avgDownTime,
                                                                     uint32_t avgConfigureTime)
    : id(id),
      totalProduced(totalProduced),
      avgProduced(avgProduced),
      totalLost(totalLost),
      avgLost(avgLost),
      avgProductionTime(avgProductionTime),
      avgIdleTime(avgIdleTime),
      avgDownTime(avgDownTime),
      avgConfigureTime(avgConfigureTime) {}

models::MachineProductFinalStatistics::MachineProductFinalStatistics(const models::MachineProductFinalStatistics &other)
    : id(other.id),
      totalProduced(other.totalProduced),
      avgProduced(other.avgProduced),
      totalLost(other.totalLost),
      avgLost(other.avgLost),
      avgProductionTime(other.avgProductionTime),
      avgIdleTime(other.avgIdleTime),
      avgDownTime(other.avgDownTime),
      avgConfigureTime(other.avgConfigureTime) {}

uint16_t models::MachineProductFinalStatistics::getId() const {
  return id;
}

uint32_t models::MachineProductFinalStatistics::getTotalProduced() const {
  return totalProduced;
}

uint16_t models::MachineProductFinalStatistics::getAvgProduced() const {
  return avgProduced;
}

uint16_t models::MachineProductFinalStatistics::getTotalLost() const {
  return totalLost;
}

uint16_t models::MachineProductFinalStatistics::getAvgLost() const {
  return avgLost;
}

uint32_t models::MachineProductFinalStatistics::getAvgProductionTime() const {
  return avgProductionTime;
}

uint32_t models::MachineProductFinalStatistics::getAvgIdleTime() const {
  return avgIdleTime;
}

uint32_t models::MachineProductFinalStatistics::getAvgDownTime() const {
  return avgDownTime;
}

uint32_t models::MachineProductFinalStatistics::getAvgConfigureTime() const {
  return avgConfigureTime;
}

}