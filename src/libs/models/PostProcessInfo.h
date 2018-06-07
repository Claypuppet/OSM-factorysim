
#ifndef PRODUCTION_LINE_CONTROL_POSTPROCESSINFO_H
#define PRODUCTION_LINE_CONTROL_POSTPROCESSINFO_H


#include <cstdint>
#include <memory>

namespace models {

class PostProcessInfo {
 public:
  PostProcessInfo(uint16_t inputDelayInSeconds, uint16_t postProcessDurationInMinutes);
  virtual ~PostProcessInfo() = default;
  PostProcessInfo(const PostProcessInfo &other);

  const uint16_t &getInputDelayInSeconds() const;
  const uint16_t &getPostProcessDurationInMinutes() const;

 private:
  uint16_t inputDelayInSeconds;
  uint16_t postProcessDurationInMinutes;
};

typedef std::shared_ptr<PostProcessInfo> PostProcessInfoPtr;

}

#endif //PRODUCTION_LINE_CONTROL_POSTPROCESSINFO_H
