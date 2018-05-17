//
// Created by don on 17-5-18.
//

#include <ctime>
#include "SystemTime.h"

uint64_t utils::SystemTime::getCurrentTime() {
  return static_cast<uint64_t >(std::clock() / 1000);
}
void utils::SystemTime::increaseCurrentTime(uint64_t increaseSeconds) {
  // Do nothing
}
void utils::SystemTime::setCurrentTime(uint64_t newTimeSeconds) {
  // Do nothing
}
