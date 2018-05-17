//
// Created by don on 17-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_SYSTEMTIME_H
#define PRODUCTION_LINE_CONTROL_SYSTEMTIME_H

#include "Time.h"

namespace utils {

/*
 * A class to keep track of the system time
 */
class SystemTime :public ITime{
 public:

  /**
   * A function to get the current system time in seconds
   * @return : System time in seconds
   */
  uint64_t getCurrentTime() override;

  /**
   * Does nothing
   */
  void increaseCurrentTime(uint64_t increaseSeconds) override;

  /**
   * Does nothing
   */
  void setCurrentTime(uint64_t newTimeSeconds) override;
};

}

#endif //PRODUCTION_LINE_CONTROL_SYSTEMTIME_H
