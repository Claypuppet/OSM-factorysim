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
#include <spdlog/sinks/file_sinks.h>
#include <spdlog/sinks/stdout_sinks.h>

namespace utils {

class FileLogger : private patterns::Singleton::Singleton<FileLogger> {
 public:
  FileLogger() = default;

  virtual ~FileLogger() = default;
  /**
   * sets up logger
   * @param filename : wished filename and extension
   * @param empty : if another file exists do we have to clear it?
   */
  static void setupLogger(const std::string &filename, bool empty = true);

  /**
   * makes a new file with the given parameters
   * @param filename wished filename and extension
   * @param empty : if another file exists do we have to clear it?
   */
  static void newFile(const std::string &filename, bool empty = true);

  /**
   * shortcut to logger of both
   * @return spdlog instance
   */
  static std::shared_ptr<spdlog::logger> both();

  /**
 * shortcut to logger of file
 * @return spdlog instance
 */
  static std::shared_ptr<spdlog::logger> file();

  /**
 * shortcut to logger of console
 * @return spdlog instance
 */
  static std::shared_ptr<spdlog::logger> console();
/**
 * changes pattern to wished format
 * @param newPattern
 */
  static void changePattern(const std::string &newPattern);
 private:
  void assignLoggers();
  std::shared_ptr<spdlog::sinks::stdout_sink_mt> consoleSink;
  std::shared_ptr<spdlog::sinks::simple_file_sink_mt> fileSink;
  std::string pattern = "%v";

};
}

#endif //PRODUCTION_LINE_CONTROL_FILELOGGER_H
