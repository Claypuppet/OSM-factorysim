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
    : networkEnabled(false), debugEnabled(false) {
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
  utils::FileLogger::getInstance().file()->info("\nevents:");
}

void ResultLogger::machineStatusUpdate(uint16_t machineId, models::Machine::MachineStatus status) {
  std::stringstream stringstream;
  stringstream << models::Machine::kMachineLogEventMachineStatusUpdate << "," << utils::Time::getInstance().getCurrentTime() << "," << machineId << "," << status;
  log(stringstream.str());
}

void ResultLogger::machineConfigChanged(uint16_t machineId, uint16_t configId) {
  std::stringstream stringstream;
  stringstream << models::Machine::kMachineLogEventMachineReconfigured << "," << utils::Time::getInstance().getCurrentTime() << "," << machineId << "," << configId;
  log(stringstream.str());
}

void ResultLogger::bufferContentsChanged(uint16_t machineId, uint16_t productId, size_t amount) {
  std::stringstream stringstream;
  stringstream << models::Machine::kMachineLogEventMachineBufferUpdate << "," << utils::Time::getInstance().getCurrentTime() << "," << machineId << "," << productId << "," << amount;
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
  utils::FileLogger::getInstance().file()->flush();
}

}