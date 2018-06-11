#include "SimulationInfo.h"

namespace models {

SimulationInfo::SimulationInfo(uint16_t durationInHours,
                               uint8_t startHourOfWorkDay,
                               uint8_t workDayDurationInHours)
    : durationInWeeks(durationInHours),
      startHourOfWorkDay(startHourOfWorkDay),
      workDayDurationInHours(workDayDurationInHours) {
}

SimulationInfo::SimulationInfo(const SimulationInfo &other)
	: durationInWeeks(other.durationInWeeks),
      startHourOfWorkDay(other.startHourOfWorkDay),
      workDayDurationInHours(other.workDayDurationInHours) {
}

SimulationInfo &SimulationInfo::operator=(const SimulationInfo &other) {
  if (this != &other) {
	durationInWeeks = other.durationInWeeks;
    startHourOfWorkDay = other.startHourOfWorkDay;
    workDayDurationInHours = other.workDayDurationInHours;
  }
  return *this;
}

uint16_t SimulationInfo::getDurationInWeeks() const {
  return durationInWeeks;
}

uint8_t SimulationInfo::getStartHourOfWorkDay() const {
  return startHourOfWorkDay;
}

uint8_t SimulationInfo::getWorkDayDurationInHours() const {
  return workDayDurationInHours;
}

}