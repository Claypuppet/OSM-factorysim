
#ifndef PRODUCTION_LINE_CONTROL_POSTPROCESSINFO_H
#define PRODUCTION_LINE_CONTROL_POSTPROCESSINFO_H


#include <cstdint>
#include <memory>

namespace models {

/**
 * Information about the post-process of a machine, used by eg Paint machine, where the post process is drying.
 */
class PostProcessInfo {
 public:
  PostProcessInfo(uint16_t inputDelayInSeconds, uint16_t postProcessDurationInMinutes);
  virtual ~PostProcessInfo() = default;
  PostProcessInfo(const PostProcessInfo &other);

  const uint16_t &getInputDelayInSeconds() const;
  const uint16_t &getPostProcessDurationInMinutes() const;

  /**
   * get input delay in milliseconds
   * @return : delay in milliseconds
   */
  const uint32_t getInputDelayInMillis() const;
  /**
   * get post process duration in milliseconds
   * @return : post process duration in milliseconds
   */
  const uint32_t getPostProcessDurationInMillis() const;

 private:
  uint16_t inputDelayInSeconds;
  uint16_t postProcessDurationInMinutes;
};

typedef std::shared_ptr<PostProcessInfo> PostProcessInfoPtr;

}

#endif //PRODUCTION_LINE_CONTROL_POSTPROCESSINFO_H
