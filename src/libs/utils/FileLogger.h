//
// Created by don on 23-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_FILELOGGER_H
#define PRODUCTION_LINE_CONTROL_FILELOGGER_H

#include <iostream>
#include <mutex>

#include <spdlog/logger.h>
#include <spdlog/sinks/file_sinks.h>
#include <spdlog/sinks/stdout_sinks.h>

#include <patterns/singleton/Singleton.h>
#include <patterns/producerconsumer/Queue.h>

namespace utils {
/**
 * The filelogger has functions to set up a logger, the setupLogger function MUST be used before using the other functions
 * It has shortcuts to spdlog::logger instances and helper function to flush all loggers
 */
class FileLogger : public patterns::singleton::Singleton<FileLogger> {
 public:

  virtual ~FileLogger() = default;
  /**
   * sets up logger
   * @param filename : wished filename and extension
   * @param empty : if another file exists do we have to clear it?
   */
  void setupLogger(const std::string &filename, bool empty = false);

  /**
   * makes a new file with the given parameters
   * @param filename wished filename and extension
   * @param empty : if another file exists do we have to clear it?
   */
  void newFile(const std::string &filename, bool empty = false);
/**
 * changes pattern to wished format
 * @param newPattern
 */
  void changePattern(const std::string &newPattern);
  /**
   * helper function to flush all loggers before continueing
   */
  void flushLoggers();

  /**
   * Log to both console and file
   * @param message : The message to log
   */
  void logToBoth(const std::string &message);

  /**
   * Log to file
   * @param message : The message to log
   */
  void logToFile(const std::string &message);

  /**
   * Log to console
   */
  void logToConsole(const std::string &message);

 private:
  friend patterns::singleton::Singleton<FileLogger>;
  FileLogger();

  /**
   * shortcut to logger of both
   * @return spdlog instance
   */
  std::shared_ptr<spdlog::logger> both();

  /**
   * shortcut to logger of file
   * @return spdlog instance
   */
  std::shared_ptr<spdlog::logger> file();

  /**
   * shortcut to logger of console
   * @return spdlog instance
   */
  std::shared_ptr<spdlog::logger> console();

  /**
   * assign loggers to spdlog
   */
  void assignLoggers();

  std::shared_ptr<spdlog::sinks::stdout_sink_mt> consoleSink;
  std::shared_ptr<spdlog::sinks::rotating_file_sink_mt> fileSink;
  std::string pattern;

};
}

#endif //PRODUCTION_LINE_CONTROL_FILELOGGER_H
