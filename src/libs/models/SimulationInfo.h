#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONINFOCONFIG_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONINFOCONFIG_H

// standard library includes
#include <memory>

// library includes
#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/node.h>
#include <cereal/cereal.hpp>

// other includes
// -

namespace models {

/**
 * Class that holds information about a simulation
 * Duration of the simulation, time of day te production starts and the production time on a day
 */
class SimulationInfo;
typedef std::shared_ptr<SimulationInfo> SimulationInfoPtr;

class SimulationInfo {
 public:
  SimulationInfo() = default;
  virtual ~SimulationInfo() = default;

  /**
   * Construct a new SimulationFile object
   * @param durationInHours the duration of the simulation in hours
   * @param startHourOfWorkDay the start hours number of the work day (the production line turns on)
   * @param workDayDurationInHours the number of hours a productionline produces
   */
  SimulationInfo(uint16_t durationInHours, uint8_t startHourOfWorkDay, uint8_t workDayDurationInHours);

  /**
   * Copy constructor
   * @param other : The object to copy
   */
  SimulationInfo(const SimulationInfo &other);

  /**
   * Assignment operator
   * @param other : The object to assign
   * @return The new object
   */
  SimulationInfo &operator=(const SimulationInfo &other);

  uint16_t getDurationInHours() const;
  uint8_t getStartHourOfWorkDay() const;
  uint8_t getWorkDayDurationInHours() const;

 private:
  uint16_t durationInHours;
  uint8_t startHourOfWorkDay;
  uint8_t workDayDurationInHours;

  /**
   * A function to serialize a SimulationInfo object from an archive
   * @tparam Archive
   * @param ar : The archive to load
   */
  template<class Archive>
  void serialize(Archive &ar) {
	ar(durationInHours,
       startHourOfWorkDay,
       workDayDurationInHours);
  }

  friend class cereal::access;
};

}

#endif //PRODUCTION_LINE_CONTROL_SIMULATIONINFOCONFIG_H
