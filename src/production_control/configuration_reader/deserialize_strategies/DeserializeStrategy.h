
#ifndef PRODUCTION_LINE_CONTROL_STRATEGY_H
#define PRODUCTION_LINE_CONTROL_STRATEGY_H

#include <string>

#include <models/Configuration.h>

namespace configurationserializer {

/**
 * Class defines interface for a deserialize strategy.
 * A deserialize strategy is meant to deserialize a configuration file
 */
class DeserializeStrategy : public std::enable_shared_from_this<DeserializeStrategy> {
 public:
  DeserializeStrategy() = default;
  virtual ~DeserializeStrategy() = default;

  /**
   * Interface for the derserialize method which deserializes a configuration file by filepath.
   * @param filePath file path to the configuration file
   * @return pointer to the deserialized configuration model
   */
  virtual const std::shared_ptr<models::Configuration> deserialize(const std::string &filePath) const = 0;
};

}


#endif //PRODUCTION_LINE_CONTROL_STRATEGY_H
