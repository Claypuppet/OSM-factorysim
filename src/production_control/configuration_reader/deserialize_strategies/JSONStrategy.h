//
// Created by bas on 23-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_JSONSTRATEGY_H
#define PRODUCTION_LINE_CONTROL_JSONSTRATEGY_H

#include <models/Configuration.h>

#include "Strategy.h"

class JSONStrategy : public Strategy {
 public:
  explicit JSONStrategy() = default;
  virtual ~JSONStrategy() = default;

  JSONStrategy(const JSONStrategy &other);

  std::shared_ptr<models::Configuration> deserialize(const std::string &filePath);
};

#endif //PRODUCTION_LINE_CONTROL_JSONSTRATEGY_H
