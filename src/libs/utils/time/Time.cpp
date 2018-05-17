//
// Created by don on 17-5-18.
//

#include "Time.h"
#include "SystemTime.h"
#include "CustomTime.h"

namespace utils {

Time::Time() {
  timer = std::make_shared<SystemTime>();
}

uint64_t Time::getCurrentTime() {
  return timer->getCurrentTime();
}
void Time::setCurrentTime(uint64_t newTimeSeconds) {
  timer->setCurrentTime(newTimeSeconds);
}
void Time::increaseCurrentTime(uint64_t increaseSeconds) {
  timer->increaseCurrentTime(increaseSeconds);
}
void Time::setType(utils::TimeType aType) {
  switch(aType)
  {
    case TimeType::systemTime:
      timer = std::make_shared<SystemTime>();
      break;
    case TimeType::customTime:
      timer = std::make_shared<CustomTime>();
      break;
    default:

      break;
  }
}

}
