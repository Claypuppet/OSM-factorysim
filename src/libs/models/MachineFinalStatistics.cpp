//
// Created by don on 6-6-18.
//

#include "MachineFinalStatistics.h"

namespace models {

MachineFinalStatistics::MachineFinalStatistics(const std::map<uint16_t, uint16_t> &producedProducts,
                                               const std::map<uint16_t, uint16_t> &lostProducts,
                                               uint32_t downTime,
                                               uint32_t productionTime,
                                               uint32_t idleTime,
                                               uint32_t configureTime,
                                               uint32_t totalProducedProducts,
                                               uint32_t totalLostProducts,
                                               uint16_t MTBF) : MachineStatistics(producedProducts,
                                                                                  lostProducts,
                                                                                  downTime,
                                                                                  productionTime,
                                                                                  idleTime,
                                                                                  configureTime),
                                                                totalProducedProducts(totalProducedProducts),
                                                                totalLostProducts(totalLostProducts),
                                                                MTBF(MTBF) {}
                                                                
uint32_t MachineFinalStatistics::getTotalProducedProducts() const {
  return totalProducedProducts;
}

uint32_t MachineFinalStatistics::getTotalLostProducts() const {
  return totalLostProducts;
}

uint16_t MachineFinalStatistics::getMTBF() const {
  return MTBF;
}

}