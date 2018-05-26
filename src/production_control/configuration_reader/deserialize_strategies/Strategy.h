//
// Created by bas on 23-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_STRATEGY_H
#define PRODUCTION_LINE_CONTROL_STRATEGY_H

#include <string>

#include <models/Configuration.h>

class Strategy : public std::enable_shared_from_this<Strategy> {
 public:
  Strategy() = default;
  virtual ~Strategy() = default;

  virtual const std::shared_ptr<models::Configuration> deserialize(const std::string &filePath) const = 0;
};


#endif //PRODUCTION_LINE_CONTROL_STRATEGY_H
