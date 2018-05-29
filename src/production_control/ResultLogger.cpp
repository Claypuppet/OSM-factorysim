//
// Created by sven on 18-5-18.
//

#include <iostream>
#include <sstream>
#include <utils/time/Time.h>
#include <utils/FileLogger.h>
#include <fstream>
#include "ResultLogger.h"

namespace core {

ResultLogger::ResultLogger()
    : networkEnabled(false), debugEnabled(true) {
}

void ResultLogger::initializeLog(const std::string &configurationPath, const std::string &configurationName) {
  std::stringstream ss;
  ss << "./" << configurationName << ".yaml";
  auto outputFileName = ss.str();

  // Copy used config as base for the production results
  std::ifstream  src(configurationPath, std::ios::binary);
  std::ofstream  dst(outputFileName, std::ios::binary);
  dst << src.rdbuf();

  // Setup logger
  utils::FileLogger::getInstance().setupLogger(outputFileName, false);
}

void ResultLogger::MachineStatusUpdate(uint16_t machineId, models::Machine::MachineStatus status) {
  std::stringstream stringstream;
  stringstream << "1," << utils::Time::getInstance().getCurrentTime() << "," << machineId << "," << status;
  log(stringstream.str());
}

void ResultLogger::MachineConfigChanged(uint16_t machineId, uint16_t configId) {
  std::stringstream stringstream;
  stringstream << "2," << utils::Time::getInstance().getCurrentTime() << "," << machineId << "," << configId;
  log(stringstream.str());
}

void ResultLogger::BufferContentsChanged(uint16_t machineId, uint16_t productId, size_t amount) {
  std::stringstream stringstream;
  stringstream << "3," << utils::Time::getInstance().getCurrentTime() << "," << machineId << "," << productId << "," << amount;
  log(stringstream.str());
}

void ResultLogger::log(const std::string &message) {
  std::stringstream logRow;
  logRow << "- " << message;
  if (debugEnabled) {
    utils::FileLogger::getInstance().both()->info(logRow.str());
  }
  else {
    utils::FileLogger::getInstance().file()->info(logRow.str());
  }
}

}