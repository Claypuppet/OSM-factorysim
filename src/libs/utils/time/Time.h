//
// Created by don on 17-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_TIME_H
#define PRODUCTION_LINE_CONTROL_TIME_H

#include <cstdint>
#include <memory>
#include "patterns/singleton/Singleton.h"

namespace utils {

enum TimeType {
  systemTime, customTime
};

/*
 * Interface class for Time strategy's
 */
class ITime {
 public:
  /**
   * A function to get the current time in seconds
   * @return : Current time in seconds
   */
  virtual uint64_t getCurrentTime() = 0;

  /**
   * A function to increase the current time in seconds
   * @param increaseSeconds : Amount of seconds to increase the current time with
   */
  virtual void increaseCurrentTime(uint64_t increaseMillis) = 0;

  /**
   * A function to set the current time in seconds
   * @param newTimeSeconds : The new current time in seconds
   */
  virtual void setCurrentTime(uint64_t newTimeMillis) = 0;
};

/*
 * A class to keep track of time in seconds
 */
class Time : public patterns::singleton::Singleton<Time> {
 public:
  Time(const Time &) = delete;
  Time &operator=(const Time &) = delete;

  /**
   * Executes the getCurrentTime function of the set strategy
   * @return : Current time in seconds
   */
  uint64_t getCurrentTime();

  /**
   * Executes the setCurrentTime function of the set strategy
   * @param newTimeSeconds : The new time in seconds
   */
  void setCurrentTime(uint64_t
					  newTimeSeconds);

  /**
   * Executes the increaseCurrentTime function of the set strategy
   * @param increaseSeconds : Amount of seconds to increase the current time with
   */
  void increaseCurrentTime(uint64_t increaseSeconds);

  /**
   * Sets the type of strategy
   * @param aType : Type of strategy to use
   */
  void setType(TimeType aType);

 protected:
  Time();
 private:
  std::shared_ptr<ITime> timer;
};

}

#endif //PRODUCTION_LINE_CONTROL_TIME_H
