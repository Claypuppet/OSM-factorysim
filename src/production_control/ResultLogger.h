//
// Created by sven on 18-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_RESULTLOGGER_H
#define PRODUCTION_LINE_CONTROL_RESULTLOGGER_H

#include <string>
#include <patterns/singleton/Singleton.h>

namespace core {

/**
 *The resultlogger class has helper functions to build logging lines for the production or simulation
 */
class ResultLogger : public patterns::singleton::Singleton<ResultLogger> {
 public:
  ResultLogger();
  virtual ~ResultLogger() = default;


  /**
   * enable or disable logging of ProductionEvents
   * @param enabled
   */
  static void setProductionEnabled(bool enabled);


  /**
   * enable or disable verbose logging of ProductionEvents
   * @param message : string to log
   */
  static void setProductionDebugOutput(bool enabled);
  /**
   * Log a productionMessage
   * @param eventId : Id of event
   * @param machineId : Id of machine
   */
  static void LogProductionEvent(uint32_t machineId, uint32_t eventId);


 private:
  bool productionEnabled;
  bool productionDebug;

};
}
#endif //PRODUCTION_LINE_CONTROL_RESULTLOGGER_H
