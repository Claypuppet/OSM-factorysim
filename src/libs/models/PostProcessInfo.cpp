
#include <cstdint>
#include "PostProcessInfo.h"

namespace models {

PostProcessInfo::PostProcessInfo(uint16_t inputDelayInSeconds, uint16_t postProcessDurationInMinutes)
    : inputDelayInSeconds(inputDelayInSeconds),
      postProcessDurationInMinutes(postProcessDurationInMinutes) {
}

PostProcessInfo::PostProcessInfo(const PostProcessInfo &other)
    : inputDelayInSeconds(other.inputDelayInSeconds),
      postProcessDurationInMinutes(other.postProcessDurationInMinutes) {
}

const uint16_t &PostProcessInfo::getInputDelayInSeconds() const {
  return inputDelayInSeconds;
}

const uint16_t &PostProcessInfo::getPostProcessDurationInMinutes() const {
  return postProcessDurationInMinutes;
}

const uint32_t PostProcessInfo::getInputDelayInMillis() const {
  return 1000u * inputDelayInSeconds;
}

const uint32_t PostProcessInfo::getPostProcessDurationInMillis() const {
  return 60000u * postProcessDurationInMinutes;
}

}