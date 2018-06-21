//
// Created by don on 12-6-18.
//

#ifndef PRODUCTION_LINE_CONTROL_FINALSTATISTICS_H
#define PRODUCTION_LINE_CONTROL_FINALSTATISTICS_H

#include <cstdint>
#include <map>
#include <memory>

namespace models {

class FinalStatistics {
 public:
  FinalStatistics(const std::map<uint16_t, uint32_t> &producedEndProducts,
                  uint16_t timesReconfigured,
                  uint32_t simulationDurationInHours);
  
  FinalStatistics(const FinalStatistics &other);
  
  const std::map<uint16_t, uint32_t> &getProducedEndProducts() const;
  uint16_t getTimesReconfigured() const;
  uint32_t getSimulationDurationInHours() const;
 private:
  std::map<uint16_t, uint32_t> producedEndProducts;
  uint16_t timesReconfigured;
  uint32_t simulationDurationInHours;
};

typedef std::shared_ptr<FinalStatistics> FinalStatisticsPtr;

}

#endif //PRODUCTION_LINE_CONTROL_FINALSTATISTICS_H
