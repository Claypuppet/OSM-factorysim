//
// Created by sven on 18-5-18.
//

#include <iostream>
#include <sstream>
#include <fstream>

#include <boost/filesystem.hpp>

#include <spdlog/spdlog.h>
#include <utils/time/Time.h>
#include <utils/FileLogger.h>

#include "ResultLogger.h"

namespace core {

// Consts used as name for filelogger (used by spdlog)
const std::string DAY_LOG_NAME = "daylog";
const std::string STATISTICS_LOG = "statistics";

ResultLogger::ResultLogger() : networkEnabled(false), debugEnabled(false) {
}

void ResultLogger::initializeLog(const std::string &configurationPath, const std::string &configurationName) {
  this->configurationName = configurationName;
  // Remove existing directory

  // create directories to log to
  std::stringstream dirToCreate;
  dirToCreate << "./" << configurationName;
  boost::filesystem::path dir(dirToCreate.str().c_str());

  if (boost::filesystem::exists(dirToCreate.str())){
    boost::filesystem::remove_all(dirToCreate.str());
  }

  boost::filesystem::create_directory(dir);

  dirToCreate << "/daily_logs";
  dir = dirToCreate.str().c_str();
  boost::filesystem::create_directory(dir);

  std::stringstream statisticsLocation;
  statisticsLocation << "./" << configurationName <<  "/statistics.json";

  utils::FileLogger::getInstance().addFileLogger(STATISTICS_LOG, statisticsLocation.str());

  std::stringstream usedConfigName;
  usedConfigName << "./" << configurationName << "/used_config.yaml";

  // Copy used config as base for the production results
  std::ifstream src(configurationPath, std::ios::binary);
  std::ofstream dst(usedConfigName.str(), std::ios::binary);
  dst << src.rdbuf();

  setNewDayLogger();
}

void ResultLogger::setNewDayLogger() {
  // Setup daily logger
  std::stringstream dailyLogLocation;
  dailyLogLocation << "./" << configurationName << "/daily_logs/" << utils::Time::getInstance().getCurrentTimeString("%Y_%m_%d") << "-log.yaml";
  auto &logger = utils::FileLogger::getInstance();
  logger.addFileLogger(DAY_LOG_NAME, dailyLogLocation.str());
  logger.get(DAY_LOG_NAME)->info("events:");

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
  utils::FileLogger::getInstance().get(DAY_LOG_NAME)->info(logRow.str());
}

void ResultLogger::logStatistics(
    const std::map<uint64_t, std::vector<models::MachineStatisticsPtr>> timeStampStatistics,
    const std::vector<models::MachineFinalStatistics> &finalStats) {

  auto logger = utils::FileLogger::getInstance().get(STATISTICS_LOG);

  logger->info("{");
  logTimeStampStatistics(timeStampStatistics);
  logFinalStatistics(finalStats);
  logger->info("}");

  utils::FileLogger::getInstance().flush(STATISTICS_LOG);
}

void ResultLogger::logTimeStampStatistics(const std::map<uint64_t,
                                                         std::vector<models::MachineStatisticsPtr>> &timeStamps) {
  auto logger = utils::FileLogger::getInstance().get(STATISTICS_LOG);

  logger->info("\t\"timeStamps\":\n\t[");

  bool firstTimeStamp = true;

  for (auto &item : timeStamps) {

    if (!firstTimeStamp) {
      logger->info("\t\t},");
    }

    firstTimeStamp = false;

    logger->info("\t\t{");
    std::stringstream weekInfo;
    weekInfo << "\t\t\t\"timeStamp\" : " << item.first << ",";
    logger->info(weekInfo.str());
    logger->info("\t\t\t\"machines\" : [");

    bool firstMachine = true;

    for (auto &machineStats : item.second) {

      if (!firstMachine) {
        logger->info("\t\t\t\t},");
      }
      firstMachine = false;

      logger->info("\t\t\t\t{");

      std::stringstream idInfo;
      idInfo << "\t\t\t\t\t\"id\" : " << machineStats->getMachineId() << ",";
      logger->info(idInfo.str());

      std::stringstream producedProducts;
      producedProducts << "\t\t\t\t\t\"producedProducts\" : {";
      for (auto &item1 : machineStats->getProducedProducts()) {
        producedProducts << "\"" << item1.first << "\"" << ":" << item1.second << ",";
      }
      if (producedProducts.str()[producedProducts.str().size() - 1] == ',') {
        producedProducts.seekp(-1, std::ios_base::end);
      }
      producedProducts << "},";
      logger->info(producedProducts.str());

      std::stringstream lostProducts;
      lostProducts << "\t\t\t\t\t\"lostProducts\" : {";
      for (auto &item1 : machineStats->getLostProducts()) {
        lostProducts << "\"" << item1.first << "\"" << ":" << item1.second << ",";
      }
      if (lostProducts.str()[lostProducts.str().size() - 1] == ',') {
        lostProducts.seekp(-1, std::ios_base::end);
      }
      lostProducts << "},";
      logger->info(lostProducts.str());

      std::stringstream downTime;
      downTime << "\t\t\t\t\t\"downTime\" : " << machineStats->getDownTime() << ",";
      logger->info(downTime.str());

      std::stringstream productionTime;
      productionTime << "\t\t\t\t\t\"productionTime\" : " << machineStats->getProductionTime() << ",";
      logger->info(productionTime.str());

      std::stringstream idleTime;
      idleTime << "\t\t\t\t\t\"idleTime\" : " << machineStats->getIdleTime() << ",";
      logger->info(idleTime.str());

      std::stringstream configureTime;
      configureTime << "\t\t\t\t\t\"configureTime\" : " << machineStats->getConfigureTime();
      logger->info(configureTime.str());
    }
    logger->info("\t\t\t\t}");
    logger->info("\t\t\t]");
  }
  logger->info("\t\t}");
  logger->info("\t],");
}

void ResultLogger::logFinalStatistics(const std::vector<models::MachineFinalStatistics> &finalStatistics) {
  auto logger = utils::FileLogger::getInstance().get(STATISTICS_LOG);

  logger->info("\t\"finalStatistics\":");
  logger->info("\t{");
  logger->info("\t\t\"machines\":");
  logger->info("\t\t[");

  bool first = true;

  for (auto &stats : finalStatistics) {

    if (!first) {
      logger->info("\t\t\t},");
    }

    first = false;

    logger->info("\t\t\t{");

    std::stringstream idStream;
    idStream << "\t\t\t\t\"id\" : " << stats.getMachineId() << ",";
    logger->info(idStream.str());

    std::stringstream totalProducedStream;
    totalProducedStream << "\t\t\t\t\"totalProducedProducts\" : {";
    for (auto &item : stats.getTotalProducedProducts()) {
      totalProducedStream << "\"" << item.first << "\":" << item.second << ",";
    }
    if (totalProducedStream.str()[totalProducedStream.str().size() - 1] == ',') {
      totalProducedStream.seekp(-1, std::ios_base::end);
    }
    totalProducedStream << "},";
    logger->info(totalProducedStream.str());

    std::stringstream avgProducedStream;
    avgProducedStream << "\t\t\t\t\"avgProducedProducts\" : {";
    for (auto &item : stats.getAvgProducedProducts()) {
      avgProducedStream << "\"" << item.first << "\":" << item.second << ",";
    }
    if (avgProducedStream.str()[avgProducedStream.str().size() - 1] == ',') {
      avgProducedStream.seekp(-1, std::ios_base::end);
    }
    avgProducedStream << "},";
    logger->info(avgProducedStream.str());

    std::stringstream totalLostStream;
    totalLostStream << "\t\t\t\t\"totalLostProducts\" : {";
    for (auto &item : stats.getTotalLostProducts()) {
      totalLostStream << "\"" << item.first << "\":" << item.second << ",";
    }
    if (totalLostStream.str()[totalLostStream.str().size() - 1] == ',') {
      totalLostStream.seekp(-1, std::ios_base::end);
    }
    totalLostStream << "},";
    logger->info(totalLostStream.str());

    std::stringstream avgLostStream;
    avgLostStream << "\t\t\t\t\"avgLostProducts\" : {";
    for (auto &item : stats.getAvgLostProducts()) {
      avgLostStream << "\"" << item.first << "\":" << item.second << ",";
    }
    if (avgLostStream.str()[avgLostStream.str().size() - 1] == ',') {
      avgLostStream.seekp(-1, std::ios_base::end);
    }
    avgLostStream << "},";
    logger->info(avgLostStream.str());

    std::stringstream productionStream;
    productionStream << "\t\t\t\t\"avgProductionTime\" : " << stats.getAvgProductionTime() << ",";
    logger->info(productionStream.str());

    std::stringstream idleStream;
    idleStream << "\t\t\t\t\"avgIdleTime\" : " << stats.getAvgIdleTime() << ",";
    logger->info(idleStream.str());

    std::stringstream downTimeStream;
    downTimeStream << "\t\t\t\t\"avgDownTime\" : " << stats.getAvgDownTime() << ",";
    logger->info(downTimeStream.str());

    std::stringstream configureStream;
    configureStream << "\t\t\t\t\"avgConfigureTime\" : " << stats.getAvgConfigureTime() << ",";
    logger->info(configureStream.str());

    std::stringstream mtbfStream;
    mtbfStream << "\t\t\t\t\"MTBFinHours\" : " << stats.getMTBFinHours();
    logger->info(mtbfStream.str());
  }
  logger->info("\t\t\t}");
  logger->info("\t\t]");
  logger->info("\t}");
}

}