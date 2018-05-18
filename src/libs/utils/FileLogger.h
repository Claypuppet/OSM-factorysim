//
// Created by don on 23-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_FILELOGGER_H
#define PRODUCTION_LINE_CONTROL_FILELOGGER_H

#include <patterns/singleton/Singleton.h>
#include <patterns/producerconsumer/Queue.h>

#include <iostream>
#include <mutex>
#include <spdlog/logger.h>

namespace utils {

class FileLogger {
 public:
  FileLogger() = default;

  virtual ~FileLogger() = default;
  /**
 * sets up logger
 * @return
 */
  static void setupLogger(std::string filename, int8_t maxFileSize);

  /**
   * shortcut to logger of both
   * @return
   */
  static std::shared_ptr<spdlog::logger> both();

  /**
 * shortcut to logger of file
 * @return
 */
  static std::shared_ptr<spdlog::logger> file();

  /**
 * shortcut to logger of console
 * @return
 */

  static std::shared_ptr<spdlog::logger> console();

//  //machine id: string,  eventid:
//  static void logMachineMessage();


};
}

#endif //PRODUCTION_LINE_CONTROL_FILELOGGER_H
