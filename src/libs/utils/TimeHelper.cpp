//
// Created by klei on 6/8/18.
//

#include <utils/time/Time.h>
#include "TimeHelper.h"
#include "Logger.h"
#include "FileLogger.h"

namespace utils {

const uint32_t hourInMillis = 3600000;
const uint16_t minuteInMillis = 60000;
const uint8_t daysInWeek = 7;

TimeHelper::TimeHelper()
    : workDayStartHour(0),
      workDayDuration(0),
      lastWorkDayStart(0),
      currentDayOfWeek(0),
      currentWeek(0) {

}

uint16_t TimeHelper::getCurrentWeek() const {
  return currentWeek;
}

void TimeHelper::initialize(uint32_t aWorkDayStartHour, uint8_t aWorkDayDuration) {
  reset();
  workDayDuration = aWorkDayDuration;
  workDayStartHour = aWorkDayStartHour;

  // Set first work day
  auto &time = Time::getInstance();
  lastWorkDayStart = time.getCurrentTime() + (hourInMillis * workDayStartHour);
  time.syncTime(lastWorkDayStart);
  FileLogger::getInstance().get(CONSOLE_LOG)->info("_______________________\nThe very first week has started! " + std::to_string(currentWeek + 1));
  FileLogger::getInstance().get(CONSOLE_LOG)->info("The very first day of work has started! " + time.getCurrentTimeString("%d-%m-%Y"));
}

uint64_t TimeHelper::getStartOfNextWorkDay() {
  uint64_t nextStart = lastWorkDayStart;
  // Increase by 1 day in millis * the number of days
  nextStart += ((24 * hourInMillis) * (currentDayOfWeek == 4 /* firday */ ? 3 : 1));
  return nextStart;
}

void TimeHelper::goToNextWorkDay() {
  // Increase work day
  do {
    lastWorkDayStart += (24 * hourInMillis);
    ++currentDayOfWeek;
    currentDayOfWeek %= daysInWeek;
  } while (currentDayOfWeek == 5 || currentDayOfWeek == 6); // Skip weekend...
  // Increase week if monday
  if (currentDayOfWeek == 0) {
    ++currentWeek;
    FileLogger::getInstance().get(CONSOLE_LOG)->info("_______________________\nA new week has started! " + std::to_string(currentWeek + 1));
  }
  auto &time = Time::getInstance();
  if (time.getCurrentTime() > lastWorkDayStart) {
    throw std::runtime_error("Wow you can't do this... the new work day already started for some reason!");
  }
  time.syncTime(lastWorkDayStart);
  FileLogger::getInstance().get(CONSOLE_LOG)->info("A new day has started! " + time.getCurrentTimeString("%d-%m-%Y"));
}

bool TimeHelper::isClosingTime(uint16_t finishUpMinutes /* = 5 */) const {
  uint64_t workDayEnd = lastWorkDayStart + (workDayDuration * hourInMillis) - (finishUpMinutes * minuteInMillis);
  return Time::getInstance().getCurrentTime() > workDayEnd;
}

void TimeHelper::reset() {
  workDayDuration = 0;
  workDayStartHour = 0;
  lastWorkDayStart = 0;
  currentDayOfWeek = 0;
  currentWeek = 0;
}
uint32_t TimeHelper::getTotalHoursWorked() {
  return static_cast<uint32_t>(((currentWeek - 1) * 5 + currentDayOfWeek) * workDayDuration);
}

}
