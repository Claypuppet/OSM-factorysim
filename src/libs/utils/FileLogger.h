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

const std::string CONSOLE_LOG = "console";

typedef std::shared_ptr<spdlog::logger> LoggerPtr;

/**
 * The filelogger has functions to set up a logger, the setupLogger function MUST be used before using the other functions
 * It has shortcuts to spdlog::logger instances and helper function to flush all loggers
 */
class FileLogger : public patterns::singleton::Singleton<FileLogger> {
 public:
  FileLogger(const FileLogger&) = delete;
  virtual ~FileLogger() = default;

  /**
   * changes pattern to wished format
   * @param newPattern
   */
  void changePattern(const std::string &newPattern);

  /**
   * Add a new file log
   * @param name : name, used to get the logger
   * @param location : filename
   * @param clearExisting : if set to true, empties the existing file
   * @return : The created filelogger
   */
  LoggerPtr addFileLogger(const std::string &name, const std::string &location, bool clearExisting = true);

  /**
   * Get logger by name
   * @param name : name of logger
   * @return : logger
   */
  LoggerPtr get(const std::string &name);

  /**
   * Flush logger
   * @param name : name of logger
   */
  void flush(const std::string &name);

  /**
   * If useDebug is false, nothing will be logged to console sink
   * @param useDebug
   */
  void useConsoleLogger(bool useDebug);

  /**
   * If debug is true, all new file loggers will also log to console.
   * @param debug
   */
  void setDebug(bool debug);

 private:
  friend patterns::singleton::Singleton<FileLogger>;
  FileLogger();

  bool debug;
  std::string pattern;
  std::shared_ptr<spdlog::sinks::stdout_sink_mt> consoleSink;
};
}

#endif //PRODUCTION_LINE_CONTROL_FILELOGGER_H
