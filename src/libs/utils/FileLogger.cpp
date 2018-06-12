//
// Created by sven on 17-5-18.
//

#include <thread>
#include <spdlog/spdlog.h>
#include <fstream>
#include "FileLogger.h"

namespace utils {

FileLogger::FileLogger() : debug(false), pattern("%v"), consoleSink(std::make_shared<spdlog::sinks::stdout_sink_mt>()){
  spdlog::register_logger(std::make_shared<spdlog::logger>(CONSOLE_LOG, consoleSink));
  useConsoleLogger(false);
}

void FileLogger::setDebug(bool aDebug) {
  debug = aDebug;
}

void FileLogger::useConsoleLogger(bool useDebug) {
  if (useDebug){
    consoleSink->set_level(spdlog::level::info);
  }
  else {
    consoleSink->set_level(spdlog::level::off);
  }
}

void FileLogger::changePattern(const std::string &newPattern) {
  pattern = newPattern;
  spdlog::set_pattern(pattern);
}

LoggerPtr FileLogger::addFileLogger(const std::string &name, const std::string &location, bool clearExisting /* = true */) {
  if(auto log = get(name)){
    // already existing
    log->flush();
    spdlog::drop(name);
  }
  auto fileSink = std::make_shared<spdlog::sinks::simple_file_sink_mt>(location, clearExisting);
  if(debug){
    std::vector<spdlog::sink_ptr> bothSinks;
    bothSinks.push_back(consoleSink);
    bothSinks.push_back(fileSink);
    spdlog::register_logger(std::make_shared<spdlog::logger>(name, begin(bothSinks), end(bothSinks)));
  }
  else{
    spdlog::register_logger(std::make_shared<spdlog::logger>(name, fileSink));
  }
  spdlog::set_pattern(pattern);
  return spdlog::get(name);
}

LoggerPtr FileLogger::get(const std::string &name) {
  return spdlog::get(name);
}

void FileLogger::flush(const std::string &name) {
  if(auto logger = spdlog::get(name)){
    logger->flush();
  }
}

}
