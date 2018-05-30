//
// Created by bas on 23-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_JSONSTRATEGY_H
#define PRODUCTION_LINE_CONTROL_JSONSTRATEGY_H

#include <models/Configuration.h>

#include "YAMLStrategy.h"

namespace configurationserializer {

/**
 * Class to deserialize JSON configuration files.
 * Because YAML is a subset of JSON, the YAML library can also read JSON
 * Therefor the JSON Strategy subclasses the YAML strategy to use its functionality.
 */
class JSONStrategy : public YAMLStrategy {
 public:
  explicit JSONStrategy() = default;
  virtual ~JSONStrategy() = default;

  JSONStrategy(const JSONStrategy &other);

  std::shared_ptr<models::Configuration> deserialize(const std::string &filePath);
};

}

#endif //PRODUCTION_LINE_CONTROL_JSONSTRATEGY_H
