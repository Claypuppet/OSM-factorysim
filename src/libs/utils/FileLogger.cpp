//
// Created by sven on 17-5-18.
//

#include <thread>
#include <spdlog/spdlog.h>
#include <fstream>
#include "FileLogger.h"

namespace utils {

void FileLogger::setupLogger(std::string filename, int8_t maxFileSize) {

  // Create the file or clear it if it's not empty
  std::ofstream file(filename);
  file << "";
  file.close();
  //removes sinks if not already empty
  spdlog::drop_all();


  try {
    auto fileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(filename, 1024 * 1024 * maxFileSize, false);
    auto consoleSink = std::make_shared<spdlog::sinks::stdout_sink_st>();

    std::vector<spdlog::sink_ptr> bothSinks;
    bothSinks.push_back(consoleSink);
    bothSinks.push_back(fileSink);

    auto both = std::make_shared<spdlog::logger>("both", begin(bothSinks), end(bothSinks));
    auto file = std::make_shared<spdlog::logger>("file", fileSink);
    auto console = std::make_shared<spdlog::logger>("console", consoleSink);

    spdlog::register_logger(both);
    spdlog::register_logger(file);
    spdlog::register_logger(console);

    // see this link for custom formatting https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
    spdlog::set_pattern("(%v)");

    both->info("Hello");
    file->info("file");
    console->info("console");

  }
  catch (const spdlog::spdlog_ex &ex) {
    std::cout << "Log initialization failed: " << ex.what() << std::endl;
  }
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
