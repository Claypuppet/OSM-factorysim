//
// Created by klei on 6/8/18.
//

#ifndef PRODUCTION_LINE_CONTROL_TIMEHELPER_H
#define PRODUCTION_LINE_CONTROL_TIMEHELPER_H


#include <cstdint>
#include <patterns/singleton/Singleton.h>

namespace utils {

/**
 * Class with helper functions for time thingies
 */
class TimeHelper : public patterns::singleton::Singleton<TimeHelper> {
 public:
  /**
   * Initialise the helper
   * @param workDayStartHour : hour of start of the work day
   * @param workDayDuration  : duration of the work day in hours
   */
  void initialize(uint32_t workDayStartHour, uint8_t workDayDuration);

  /**
   * get number of weeks since start of application
   * @return : week number
   */
  uint16_t getCurrentWeek() const;

  /**
   * get the next work day millis
   * @return : time of next work day start
   */
  uint64_t getStartOfNextWorkDay();

  /**
   * Increase the time to the next day / start hour
   */
  void goToNextWorkDay();

  /**
   * checks if it is time to close down
   * @param finishUpMinutes : time in minutes as slack before workday finish. default 0
   * @return : true if the work day is over
   */
  bool isClosingTime(uint16_t finishUpMinutes = 0) const;

  /**
   * Calculates the amount of hours the production line was producing
   * @return : The total amount of hours the production line has been producing
   */
  uint32_t getTotalHoursWorked();

 private:
  friend patterns::singleton::Singleton<TimeHelper>;
  TimeHelper();
  virtual ~TimeHelper() = default;

  /**
   * Resets all fields
   */
  void reset();

  uint32_t workDayStartHour;
  uint8_t workDayDuration;

  uint64_t lastWorkDayStart;
  uint8_t currentDayOfWeek;
  uint16_t currentWeek;
};

}

#endif //PRODUCTION_LINE_CONTROL_TIMEHELPER_H
