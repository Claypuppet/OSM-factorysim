//
// Created by don on 17-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_CUSTOMTIMER_H
#define PRODUCTION_LINE_CONTROL_CUSTOMTIMER_H

#include <cstdint>
#include "Time.h"

namespace utils {

/*
 * A class to keep track of a custom time
 */
class CustomTime : public ITime {
 public:
  CustomTime();
  CustomTime(const CustomTime &) = delete;
  CustomTime &operator=(const CustomTime &) = delete;

  /**
   * @see ITimer::getCurrentTime()
   */
  uint64_t getCurrentTime() override;

  /**
   * @see ITimer::increaseCurrentTime(uint64_t increaseSeconds)
   */
  void increaseCurrentTime(uint64_t increaseSeconds) override;

  /**
   * @see ITimer::setCurrentTime(uint64_t newTimeSeconds)
   */
  void setCurrentTime(uint64_t newTimeSeconds) override;
 private:

  /**
   * Current time in milliseconds
   */
  uint64_t currentTime;
};

}

#endif //PRODUCTION_LINE_CONTROL_CUSTOMTIMER_H
