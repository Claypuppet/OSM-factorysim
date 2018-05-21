//
// Created by sven on 17-5-18.
//

#include <thread>
#include <spdlog/spdlog.h>
#include <fstream>
#include "FileLogger.h"

namespace utils {

void FileLogger::setupLogger(const std::string &filename, bool empty) {
  if (empty) {
    // Create the file or clear it if it's not empty
    std::ofstream file(filename);
    file << "";
    file.close();
  }
  try {
    getInstance().consoleSink = std::make_shared<spdlog::sinks::stdout_sink_mt>();
    getInstance().fileSink =
        std::make_shared<spdlog::sinks::simple_file_sink_mt>(filename, false);

    getInstance().assignLoggers();
  }
  catch (const spdlog::spdlog_ex &ex) {
    std::cout << "Log initialization failed: " << ex.what() << std::endl;
  }
}

void FileLogger::assignLoggers() {
  try {
    spdlog::drop_all();

    std::vector<spdlog::sink_ptr> bothSinks;
    bothSinks.push_back(consoleSink);
    bothSinks.push_back(fileSink);

    spdlog::register_logger(std::make_shared<spdlog::logger>("both", begin(bothSinks), end(bothSinks)));
    spdlog::register_logger(std::make_shared<spdlog::logger>("file", getInstance().fileSink));
    spdlog::register_logger(std::make_shared<spdlog::logger>("console", getInstance().consoleSink));

    spdlog::set_pattern(pattern);
  } catch (const spdlog::spdlog_ex &ex) {
    std::cout << "assiging loggers failed: " << ex.what() << std::endl;
  }
}

void FileLogger::changePattern(const std::string &newPattern) {
  getInstance().pattern = newPattern;
  spdlog::set_pattern(getInstance().pattern);
}

void FileLogger::newFile(const std::string &filename, bool empty) {
  if (empty) {
    // Create the file or clear it if it's not empty
    std::ofstream file(filename);
    file << "";
    file.close();
  }
  getInstance().fileSink =
      std::make_shared<spdlog::sinks::simple_file_sink_mt>(filename, false);
  getInstance().assignLoggers();
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

}
