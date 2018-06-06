
#ifndef PRODUCTION_LINE_CONTROL_POSTPROCESSINFO_H
#define PRODUCTION_LINE_CONTROL_POSTPROCESSINFO_H

#include <zconf.h>
#include <cstdint>
#include <stdint-gcc.h>

namespace models {

class PostProcessInfo {
 public:
  PostProcessInfo(uint16_t inputDelayInSeconds, uint16_t postProcessDurationInMinutes);
  virtual ~PostProcessInfo() = default;
  PostProcessInfo(const PostProcessInfo &other); // TODO : kan eigenlijk weg

  const uint16_t &getInputDelayInSeconds() const;
  const uint16_t &getPostProcessDurationInMinutes() const;

 private:
  uint16_t inputDelayInSeconds;
  uint16_t postProcessDurationInMinutes;
};

}

#endif //PRODUCTION_LINE_CONTROL_POSTPROCESSINFO_H
