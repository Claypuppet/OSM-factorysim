//
// Created by sven on 18-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_RESULTLOGGER_H
#define PRODUCTION_LINE_CONTROL_RESULTLOGGER_H

#include <string>
#include <patterns/singleton/Singleton.h>
#include "Machine.h"

namespace core {

/**
 *The resultlogger class has helper functions to build logging lines for the production or simulation
 */
class ResultLogger : public patterns::singleton::Singleton<ResultLogger> {
 public:
  virtual ~ResultLogger() = default;

  void initializeLog(const std::string &configurationPath, const std::string &configurationName);

  /**
   * Log a machine status update
   * @param machineId : Id of machine
   * @param status : machien status
   */
  void MachineStatusUpdate(uint16_t machineId, models::Machine::MachineStatus status);

  /**
   * Log a machine status update
   * @param machineId : Id of machine
   * @param status : machien status
   */
  void MachineConfigChanged(uint16_t machineId, uint16_t configId);

  /**
   * Log the contents of a buffer
   * @param machineId : Id of machine (outputbuffer)
   * @param productId : Id of the product
   * @param amount : amount of items in buffer
   */
  void BufferContentsChanged(uint16_t machineId, uint16_t productId, size_t amount);


 private:
  friend patterns::singleton::Singleton<ResultLogger>;
  ResultLogger();

  void log(const std::string &s);

  bool networkEnabled;
  bool debugEnabled;

};
}
#endif //PRODUCTION_LINE_CONTROL_RESULTLOGGER_H
