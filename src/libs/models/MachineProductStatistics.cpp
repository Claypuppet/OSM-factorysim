//
// Created by don on 12-6-18.
//

#include "MachineProductStatistics.h"

namespace models {

MachineProductStatistics::MachineProductStatistics(uint16_t productId,
                                                   uint32_t productionTime,
                                                   uint32_t downTime,
                                                   uint32_t idleTime,
                                                   uint32_t configureTime,
                                                   uint16_t produced,
                                                   uint16_t lost)
    : productId(productId),
      productionTime(productionTime),
      downTime(downTime),
      idleTime(idleTime),
      configureTime(configureTime),
      produced(produced),
      lost(lost) {}

MachineProductStatistics::MachineProductStatistics(const MachineProductStatistics &other)
    : productId(other.productId),
      productionTime(other.productionTime),
      downTime(other.downTime),
      idleTime(other.idleTime),
      configureTime(other.configureTime),
      produced(other.produced),
      lost(other.lost) {}

uint16_t MachineProductStatistics::getProductId() const {
  return productId;
}

uint32_t MachineProductStatistics::getDownTime() const {
  return downTime;
}

uint32_t MachineProductStatistics::getIdleTime() const {
  return idleTime;
}

uint32_t MachineProductStatistics::getConfigureTime() const {
  return configureTime;
}

uint16_t MachineProductStatistics::getProduced() const {
  return produced;
}

uint16_t MachineProductStatistics::getLost() const {
  return lost;
}

uint32_t MachineProductStatistics::getProductionTime() const {
  return productionTime;
}

}