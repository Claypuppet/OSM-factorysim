//
// Created by bas on 23-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_STRATEGY_H
#define PRODUCTION_LINE_CONTROL_STRATEGY_H

#include <string>

#include <models/Configuration.h>

class Strategy {
 public:
  Strategy() = default;
  virtual ~Strategy() = default;
  virtual void deserializeConfigurationFile(const std::string &filePath, models::Configuration &configuration) = 0;
};


#endif //PRODUCTION_LINE_CONTROL_STRATEGY_H
