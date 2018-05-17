//
// Created by don on 17-5-18.
//

#include "CustomTime.h"

namespace utils {

CustomTime::CustomTime() : currentTime(0) {}

uint64_t CustomTime::getCurrentTime() {
  return currentTime;
}
void CustomTime::increaseCurrentTime(uint64_t increaseSeconds) {
  currentTime += increaseSeconds;
}
void CustomTime::setCurrentTime(uint64_t newTimeSeconds) {
  currentTime = newTimeSeconds;
}

}