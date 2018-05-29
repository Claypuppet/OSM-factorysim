
#ifndef PRODUCTION_LINE_CONTROL_STRATEGY_H
#define PRODUCTION_LINE_CONTROL_STRATEGY_H

#include <string>

#include <models/Configuration.h>

namespace ConfigLoader {

class DeserializeStrategy : public std::enable_shared_from_this<DeserializeStrategy> {
 public:
  DeserializeStrategy() = default;
  virtual ~DeserializeStrategy() = default;

  virtual const std::shared_ptr<models::Configuration> deserialize(const std::string &filePath) const = 0;
};

}


#endif //PRODUCTION_LINE_CONTROL_STRATEGY_H
