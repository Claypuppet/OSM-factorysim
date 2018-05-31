#include "SimulationInfo.h"

namespace models {

SimulationInfo::SimulationInfo(uint16_t durationInHours,
                               uint8_t startHourOfWorkDay,
                               uint8_t workDayDurationInHours)
    : durationInHours(durationInHours),
      startHourOfWorkDay(startHourOfWorkDay),
      workDayDurationInHours(workDayDurationInHours) {
}

SimulationInfo::SimulationInfo(const SimulationInfo &other)
	: durationInHours(other.durationInHours),
      startHourOfWorkDay(other.startHourOfWorkDay),
      workDayDurationInHours(other.workDayDurationInHours) {
}

SimulationInfo &SimulationInfo::operator=(const SimulationInfo &other) {
  if (this != &other) {
	durationInHours = durationInHours;
    startHourOfWorkDay = startHourOfWorkDay;
    workDayDurationInHours = workDayDurationInHours;
  }

  return *this;
}

uint16_t SimulationInfo::getDurationInHours() const {
  return durationInHours;
}

uint8_t SimulationInfo::getStartHourOfWorkDay() const {
  return startHourOfWorkDay;
}

uint8_t SimulationInfo::getWorkDayDurationInHours() const {
  return workDayDurationInHours;
}

}