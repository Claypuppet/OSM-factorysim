//
// Created by don on 12-6-18.
//

#include "FinalStatistics.h"

namespace models {

FinalStatistics::FinalStatistics(const std::map<uint16_t, uint32_t> &producedEndProducts,
                                 uint16_t timesReconfigured,
                                 uint32_t simulationDurationInHours)
    : producedEndProducts(producedEndProducts),
      timesReconfigured(timesReconfigured),
      simulationDurationInHours(simulationDurationInHours) {}
const std::map<uint16_t, uint32_t> &FinalStatistics::getProducedEndProducts() const {
  return producedEndProducts;
}
uint16_t FinalStatistics::getTimesReconfigured() const {
  return timesReconfigured;
}
uint32_t FinalStatistics::getSimulationDurationInHours() const {
  return simulationDurationInHours;
}
FinalStatistics::FinalStatistics(const FinalStatistics &other)
    : producedEndProducts(other.producedEndProducts),
      timesReconfigured(other.timesReconfigured),
      simulationDurationInHours(other.simulationDurationInHours) {

}

}