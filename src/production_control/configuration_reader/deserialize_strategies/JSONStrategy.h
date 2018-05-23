//
// Created by bas on 23-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_JSONSTRATEGY_H
#define PRODUCTION_LINE_CONTROL_JSONSTRATEGY_H

#include <models/Configuration.h>

#include "Strategy.h"

class JSONStrategy : public Strategy {
 public:
  explicit JSONStrategy();
  virtual ~JSONStrategy();
  models::Configuration deserializeConfigurationFile(const std::string &filePath);
  bool deserialize();
};

#endif //PRODUCTION_LINE_CONTROL_JSONSTRATEGY_H
