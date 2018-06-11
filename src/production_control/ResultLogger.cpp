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
  std::ifstream src(configurationPath, std::ios::binary);
  std::ofstream dst(outputFileName, std::ios::binary);
  dst << src.rdbuf();

  // Setup logger
  utils::FileLogger::getInstance().setupLogger(outputFileName, false);
  utils::FileLogger::getInstance().logToFile("\nevents:");

  this->configurationName = configurationName;
}

void ResultLogger::machineStatusUpdate(uint16_t machineId, models::Machine::MachineStatus status) {
  std::stringstream stringstream;
  stringstream << models::Machine::kMachineLogEventMachineStatusUpdate << ","
               << utils::Time::getInstance().getCurrentTime() << "," << machineId << "," << status;
  log(stringstream.str());
}

void ResultLogger::machineConfigChanged(uint16_t machineId, uint16_t configId) {
  std::stringstream stringstream;
  stringstream << models::Machine::kMachineLogEventMachineReconfigured << ","
               << utils::Time::getInstance().getCurrentTime() << "," << machineId << "," << configId;
  log(stringstream.str());
}

void ResultLogger::bufferContentsChanged(uint16_t machineId, uint16_t productId, size_t amount) {
  std::stringstream stringstream;
  stringstream << models::Machine::kMachineLogEventMachineBufferUpdate << ","
               << utils::Time::getInstance().getCurrentTime() << "," << machineId << "," << productId << "," << amount;
  log(stringstream.str());
}

void ResultLogger::log(const std::string &message) {
  std::stringstream logRow;
  logRow << "- " << message;
  if (debugEnabled) {
//    utils::FileLogger::getInstance().logToBoth(logRow.str());
  }
  else {
//    utils::FileLogger::getInstance().logToFile(logRow.str());
  }
  // Temp here till we have a production shutdown.
//  utils::FileLogger::getInstance().flushLoggers();
}

void ResultLogger::logStatistics(
    const std::map<uint64_t, std::vector<models::MachineStatisticsPtr>> timeStampStatistics,
    const std::vector<models::MachineFinalStatistics> &finalStats) {
  std::stringstream outputFileName;
  outputFileName << "./" << configurationName <<  "_statistics" <<".json";

  auto &logger = utils::FileLogger::i();

  logger.setupLogger(outputFileName.str(), true);

  logger.logToFile("{");
  logTimeStampStatistics(timeStampStatistics);
  logFinalStatistics(finalStats);
  logger.logToFile("}");
  logger.flushLoggers();
}

void ResultLogger::logTimeStampStatistics(const std::map<uint64_t,
                                                         std::vector<models::MachineStatisticsPtr>> &timeStamps) {
  auto &logger = utils::FileLogger::getInstance();

  logger.logToFile("\t\"timeStamps\":\n\t[");

  bool firstTimeStamp = true;

  for (auto &item : timeStamps) {

    if (!firstTimeStamp) {
      logger.logToFile("\t\t},");
    }

    firstTimeStamp = false;

    logger.logToFile("\t\t{");
    std::stringstream weekInfo;
    weekInfo << "\t\t\t\"timeStamp\" : " << item.first << ",";
    logger.logToFile(weekInfo.str());
    logger.logToFile("\t\t\t\"machines\" : [");

    bool firstMachine = true;

    for (auto &machineStats : item.second) {

      if (!firstMachine) {
        logger.logToFile("\t\t\t\t},");
      }
      firstMachine = false;

      logger.logToFile("\t\t\t\t{");

      std::stringstream idInfo;
      idInfo << "\t\t\t\t\t\"id\" : " << machineStats->getMachineId() << ",";
      logger.logToFile(idInfo.str());

      std::stringstream producedProducts;
      producedProducts << "\t\t\t\t\t\"producedProducts\" : {";
      for (auto &item1 : machineStats->getProducedProducts()) {
        producedProducts << "\"" << item1.first << "\"" << ":" << item1.second << ",";
      }
      if (producedProducts.str()[producedProducts.str().size() - 1] == ',') {
        producedProducts.seekp(-1, std::ios_base::end);
      }
      producedProducts << "},";
      logger.logToFile(producedProducts.str());

      std::stringstream lostProducts;
      lostProducts << "\t\t\t\t\t\"lostProducts\" : {";
      for (auto &item1 : machineStats->getLostProducts()) {
        lostProducts << "\"" << item1.first << "\"" << ":" << item1.second << ",";
      }
      if (lostProducts.str()[lostProducts.str().size() - 1] == ',') {
        lostProducts.seekp(-1, std::ios_base::end);
      }
      lostProducts << "},";
      logger.logToFile(lostProducts.str());

      std::stringstream downTime;
      downTime << "\t\t\t\t\t\"downTime\" : " << machineStats->getDownTime() << ",";
      logger.logToFile(downTime.str());

      std::stringstream productionTime;
      productionTime << "\t\t\t\t\t\"productionTime\" : " << machineStats->getProductionTime() << ",";
      logger.logToFile(productionTime.str());

      std::stringstream idleTime;
      idleTime << "\t\t\t\t\t\"idleTime\" : " << machineStats->getIdleTime() << ",";
      logger.logToFile(idleTime.str());

      std::stringstream configureTime;
      configureTime << "\t\t\t\t\t\"configureTime\" : " << machineStats->getConfigureTime();
      logger.logToFile(configureTime.str());
    }
    logger.logToFile("\t\t\t\t}");
    logger.logToFile("\t\t\t]");
  }
  logger.logToFile("\t\t}");
  logger.logToFile("\t],");
}

void ResultLogger::logFinalStatistics(const std::vector<models::MachineFinalStatistics> &finalStatistics) {
  auto &logger = utils::FileLogger::getInstance();

  logger.logToFile("\t\"finalStatistics\":");
  logger.logToFile("\t{");
  logger.logToFile("\t\t\"machines\":");
  logger.logToFile("\t\t[");

  bool first = true;

  for (auto &stats : finalStatistics) {

    if (!first) {
      logger.logToFile("\t\t\t},");
    }

    first = false;

    logger.logToFile("\t\t\t{");

    std::stringstream idStream;
    idStream << "\t\t\t\t\"id\" : " << stats.getMachineId() << ",";
    logger.logToFile(idStream.str());

    std::stringstream totalProducedStream;
    totalProducedStream << "\t\t\t\t\"totalProducedProducts\" : {";
    for (auto &item : stats.getTotalProducedProducts()) {
      totalProducedStream << "\"" << item.first << "\":" << item.second << ",";
    }
    if (totalProducedStream.str()[totalProducedStream.str().size() - 1] == ',') {
      totalProducedStream.seekp(-1, std::ios_base::end);
    }
    totalProducedStream << "},";
    logger.logToFile(totalProducedStream.str());

    std::stringstream avgProducedStream;
    avgProducedStream << "\t\t\t\t\"avgProducedProducts\" : {";
    for (auto &item : stats.getAvgProducedProducts()) {
      avgProducedStream << "\"" << item.first << "\":" << item.second << ",";
    }
    if (avgProducedStream.str()[avgProducedStream.str().size() - 1] == ',') {
      avgProducedStream.seekp(-1, std::ios_base::end);
    }
    avgProducedStream << "},";
    logger.logToFile(avgProducedStream.str());

    std::stringstream totalLostStream;
    totalLostStream << "\t\t\t\t\"totalLostProducts\" : {";
    for (auto &item : stats.getTotalLostProducts()) {
      totalLostStream << "\"" << item.first << "\":" << item.second << ",";
    }
    if (totalLostStream.str()[totalLostStream.str().size() - 1] == ',') {
      totalLostStream.seekp(-1, std::ios_base::end);
    }
    totalLostStream << "},";
    logger.logToFile(totalLostStream.str());

    std::stringstream avgLostStream;
    avgLostStream << "\t\t\t\t\"avgLostProducts\" : {";
    for (auto &item : stats.getAvgLostProducts()) {
      avgLostStream << "\"" << item.first << "\":" << item.second << ",";
    }
    if (avgLostStream.str()[avgLostStream.str().size() - 1] == ',') {
      avgLostStream.seekp(-1, std::ios_base::end);
    }
    avgLostStream << "},";
    logger.logToFile(avgLostStream.str());

    std::stringstream productionStream;
    productionStream << "\t\t\t\t\"avgProductionTime\" : " << stats.getAvgProductionTime() << ",";
    logger.logToFile(productionStream.str());

    std::stringstream idleStream;
    idleStream << "\t\t\t\t\"avgIdleTime\" : " << stats.getAvgIdleTime() << ",";
    logger.logToFile(idleStream.str());

    std::stringstream downTimeStream;
    downTimeStream << "\t\t\t\t\"avgDownTime\" : " << stats.getAvgDownTime() << ",";
    logger.logToFile(downTimeStream.str());

    std::stringstream configureStream;
    configureStream << "\t\t\t\t\"avgConfigureTime\" : " << stats.getAvgConfigureTime() << ",";
    logger.logToFile(configureStream.str());

    std::stringstream mtbfStream;
    mtbfStream << "\t\t\t\t\"MTBFinHours\" : " << stats.getMTBFinHours();
    logger.logToFile(mtbfStream.str());
  }
  logger.logToFile("\t\t\t}");
  logger.logToFile("\t\t]");
  logger.logToFile("\t}");
}

}