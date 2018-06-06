
#include <cstdint>
#include "PostProcessInfo.h"

namespace models {

PostProcessInfo::PostProcessInfo(uint16_t inputDelayInSeconds, uint16_t postProcessDurationInMinutes)
    : inputDelayInSeconds(inputDelayInSeconds),
      postProcessDurationInMinutes(postProcessDurationInMinutes) {
}

const uint16_t &PostProcessInfo::getInputDelayInSeconds() const {
  return inputDelayInSeconds;
}

const uint16_t &PostProcessInfo::getPostProcessDurationInMinutes() const {
  return postProcessDurationInMinutes;
}

}