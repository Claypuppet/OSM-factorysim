//
// Created by don on 17-5-18.
//

#include <ctime>
#include "SystemTime.h"

uint64_t utils::SystemTime::getCurrentTime() {
  return static_cast<uint64_t >(std::clock()) + offset;
}

void utils::SystemTime::increaseCurrentTime(uint64_t increaseMillis) {
  // Do nothing
}

void utils::SystemTime::syncTime(uint64_t newTimeMillis) {
  offset = newTimeMillis - getCurrentTime();
}
