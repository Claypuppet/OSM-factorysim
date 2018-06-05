//
// Created by don on 5-6-18.
//

#include "MachineStatistics.h"

namespace models {

MachineStatistics::MachineStatistics(uint16_t producedProducts,
                                             uint16_t lostProducts,
                                             uint32_t downTime,
                                             uint32_t productionTime,
                                             uint32_t idleTime,
                                             uint32_t configureTime)
    : producedProducts(producedProducts),
      lostProducts(lostProducts),
      downTime(downTime),
      productionTime(productionTime),
      idleTime(idleTime),
      configureTime(configureTime) {

}

uint16_t MachineStatistics::getProducedProducts() const {
  return producedProducts;
}

uint16_t MachineStatistics::getLostProducts() const {
  return lostProducts;
}

uint32_t MachineStatistics::getDownTime() const {
  return downTime;
}

uint32_t MachineStatistics::getProductionTime() const {
  return productionTime;
}

uint32_t MachineStatistics::getIdleTime() const {
  return idleTime;
}

uint32_t MachineStatistics::getConfigureTime() const {
  return configureTime;
}

}
