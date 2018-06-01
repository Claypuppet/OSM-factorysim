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
class SystemTime : public ITime {
 public:

  /**
   * A function to get the current system time in seconds
   * @return : System time in seconds
   */
  uint64_t getCurrentTime() override;

  /**
   * Does nothing
   */
  void increaseCurrentTime(uint64_t) override;

  /**
   * Does nothing
   */
  void syncTime(uint64_t newTimeMillis) override;
  void reset() override;

 private:
  int64_t offset;
};

}

#endif //PRODUCTION_LINE_CONTROL_SYSTEMTIME_H
