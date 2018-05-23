//
// Created by sven on 18-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_RESULTLOGGER_H
#define PRODUCTION_LINE_CONTROL_RESULTLOGGER_H

#include <patterns/singleton/Singleton.h>
#include <string>

namespace core {

/**
 *The resultlogger class has helper functions to build 
 * 
 */
class ResultLogger : public patterns::singleton::Singleton<ResultLogger> {
 public:
  ResultLogger();
  virtual ~ResultLogger() = default;

  /**
   * enable or disable logging of SimulationEvents
   * @param enabled
   */
  static void setSimulationEnabled(bool enabled);
  /**
   * enable or disable logging of ProductionEvents
   * @param enabled
   */
  static void setProductionEnabled(bool enabled);

  /**
 * enable or disable verbose logging of SimulationEvents
 * @param message : string to log
 */

  static void setSimulationDebugOutput(bool enabled);
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

  /**
  * Log a simulationMessageMessage
  * @param message : string to log
  */
  void LogSimulationEvent(uint32_t eventId);

 private:
  bool productionEnabled;
  bool simulationEnabled;
  bool simulationDebug;
  bool productionDebug;

};
}
#endif //PRODUCTION_LINE_CONTROL_RESULTLOGGER_H
