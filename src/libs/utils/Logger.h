//
// Created by don on 23-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_LOGGER_H
#define PRODUCTION_LINE_CONTROL_LOGGER_H

#include <patterns/singleton/Singleton.h>
#include <patterns/producerconsumer/Queue.h>

#include <iostream>
#include <mutex>

namespace utils {

class Logger : public patterns::singleton::Singleton<Logger> {
 public:
  Logger();
  virtual ~Logger();

  /**
   * enable or disable logging
   * @param message : string to log
   */
  static void setEnabled(bool enabled);

  /**
   * Quick method for logging, calls getInstance and uses the logMessage
   * @param message : string to log
   */
  static void log(const std::string &message);

  /**
   * the actual log method
   * @param message
   */
  void logMessage(const std::string &message);

 private:

  bool enabled;
  std::mutex lock;
};

}

#endif //PRODUCTION_LINE_CONTROL_LOGGER_H
