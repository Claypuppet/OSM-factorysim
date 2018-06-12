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
   * Setup new daily logger
   */
  void setNewDayLogger();

  /**
   * Log a machine status update
   * @param machineId : Id of machine
   * @param status : machien status
   */
  void machineStatusUpdate(uint16_t machineId, models::Machine::MachineStatus status);

  /**
   * Log a machine status update
   * @param machineId : Id of machine
   * @param status : machien status
   */
  void machineConfigChanged(uint16_t machineId, uint16_t configId);

  /**
   * Log the contents of a buffer
   * @param machineId : Id of machine (outputbuffer)
   * @param productId : Id of the product
   * @param amount : amount of items in buffer
   */
  void bufferContentsChanged(uint16_t machineId, uint16_t productId, size_t amount);

  /**
   * Writes statistics of the simulation to a JSON result file
   * @param timeStampStatistics : Map with machineStatistics per time stamp
   * @param finalStats : Final statistics of the simulation
   * @return
   */
  void logStatistics(const std::map<uint64_t, std::vector<models::MachineStatisticsPtr>> timeStampStatistics,
                     const std::vector<models::MachineFinalStatistics> &finalStats);

 private:
  friend patterns::singleton::Singleton<ResultLogger>;
  ResultLogger();

  void log(const std::string &message);

  /**
   * Logs all statistics of a timestamp
   * @param machines : The machines to log the weekly statistics of
   */
  void logTimeStampStatistics(const std::map<uint64_t, std::vector<models::MachineStatisticsPtr>> &timeStamps);

  /**
   * Logs the final statistics of machines
   * @param machines : The machines to log the final statistics of
   */
  void logFinalStatistics(const std::vector<models::MachineFinalStatistics> &finalStatistics);

  bool networkEnabled;
  bool debugEnabled;

  std::string configurationName;

};
}
#endif //PRODUCTION_LINE_CONTROL_RESULTLOGGER_H
