//
// Created by don on 17-5-18.
//

#include "CustomTime.h"

namespace utils {

CustomTime::CustomTime() : currentTime(0) {}

uint64_t CustomTime::getCurrentTime() {
  return currentTime;
}
void CustomTime::increaseCurrentTime(uint64_t increaseMillis) {
  currentTime += increaseMillis;
}
void CustomTime::syncTime(uint64_t newTimeMillis) {
  if(newTimeMillis >= currentTime) {
    currentTime = newTimeMillis;
  }
  else
  {
    throw new std::runtime_error("Cannot time travel to the past only to the future!");
  }
}

}