//
// Created by sven on 17-5-18.
//

#include <thread>
#include <spdlog/spdlog.h>
#include <fstream>
#include "FileLogger.h"

namespace utils {

FileLogger::FileLogger() : pattern("%v") {
}

void FileLogger::setupLogger(const std::string &filename, bool empty) {
  consoleSink = std::make_shared<spdlog::sinks::stdout_sink_mt>();
  newFile(filename, empty);
}

void FileLogger::assignLoggers() {
  try {
    spdlog::drop_all();

    std::vector<spdlog::sink_ptr> bothSinks;
    bothSinks.push_back(consoleSink);
    bothSinks.push_back(fileSink);

    spdlog::register_logger(std::make_shared<spdlog::logger>("file", fileSink));
    spdlog::register_logger(std::make_shared<spdlog::logger>("console", consoleSink));
    spdlog::register_logger(std::make_shared<spdlog::logger>("both", begin(bothSinks), end(bothSinks)));

    spdlog::set_pattern(pattern);

  } catch (const spdlog::spdlog_ex &ex) {
    std::cout << "assiging loggers failed: " << ex.what() << std::endl;
    throw ex;
  }
}

void FileLogger::changePattern(const std::string &newPattern) {
  pattern = newPattern;
  spdlog::set_pattern(pattern);
}

void FileLogger::newFile(const std::string &filename, bool empty) {
  fileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(filename, 1048576 * 200, 1);
  assignLoggers();
}

std::shared_ptr<spdlog::logger> FileLogger::both() {
  return spdlog::get("both");
}

std::shared_ptr<spdlog::logger> FileLogger::file() {
  return spdlog::get("file");
}

std::shared_ptr<spdlog::logger> FileLogger::console() {
  return spdlog::get("console");
}

void FileLogger::flushLoggers() {
  spdlog::get("both")->flush();
}

void FileLogger::logToBoth(const std::string &message) {
  auto logger = both();
  if(logger){
    logger->info(message);
  }
}

void FileLogger::logToFile(const std::string &message) {
  auto logger = file();
  if(logger){
    logger->info(message);
  }
}

void FileLogger::logToConsole(const std::string &message) {
  auto logger = console();
  if (logger) {
    logger->info(message);
  }
}

}
