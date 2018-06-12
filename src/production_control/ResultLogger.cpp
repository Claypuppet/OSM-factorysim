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

  if (boost::filesystem::exists(dirToCreate.str())) {
    boost::filesystem::remove_all(dirToCreate.str());
  }

  boost::filesystem::create_directory(dir);

  dirToCreate << "/daily_logs";
  dir = dirToCreate.str().c_str();
  boost::filesystem::create_directory(dir);

  std::stringstream statisticsLocation;
  statisticsLocation << "./" << configurationName << "/statistics.json";

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
  dailyLogLocation << "./" << configurationName << "/daily_logs/"
                   << utils::Time::getInstance().getCurrentTimeString("%Y_%m_%d") << "-log.yaml";
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
    logger->info("\t\t\t\"machines\" :");
    logger->info("\t\t\t[");

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

      logger->info("\t\t\t\t\t\"products\" :");
      logger->info("\t\t\t\t\t[");

      bool firstProduct = true;

      for (auto &product : machineStats->getProductStatistics()) {

        if (product.getProductId() != 0) {

          if (!firstProduct) {
            logger->info("\t\t\t\t\t\t},");
          }
          firstProduct = false;

          logger->info("\t\t\t\t\t\t{");

          std::stringstream productIdStream;
          productIdStream << "\t\t\t\t\t\t\t\"productId\" : " << product.getProductId() << ",";
          logger->info(productIdStream.str());

          std::stringstream producedStream;
          producedStream << "\t\t\t\t\t\t\t\"produced\" : " << product.getProduced() << ",";
          logger->info(producedStream.str());

          std::stringstream lostStream;
          lostStream << "\t\t\t\t\t\t\t\"lost\" : " << product.getLost() << ",";
          logger->info(lostStream.str());

          std::stringstream productionTimeStream;
          productionTimeStream << "\t\t\t\t\t\t\t\"productionTime\" : " << product.getProductionTime() << ",";
          logger->info(productionTimeStream.str());

          std::stringstream idleTimeStream;
          idleTimeStream << "\t\t\t\t\t\t\t\"idleTime\" : " << product.getIdleTime() << ",";
          logger->info(idleTimeStream.str());

          std::stringstream downTimeStream;
          downTimeStream << "\t\t\t\t\t\t\t\"downTime\" : " << product.getDownTime() << ",";
          logger->info(downTimeStream.str());

          std::stringstream configureTimeStream;
          configureTimeStream << "\t\t\t\t\t\t\t\"configureTime\" : " << product.getConfigureTime();
          logger->info(configureTimeStream.str());
        }
      }
      if(!machineStats->getProductStatistics().empty()) {
        logger->info("\t\t\t\t\t\t}");
      }
      logger->info("\t\t\t\t\t]");
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

    std::stringstream nameStream;
    nameStream << "\t\t\t\t\"name\" : \"" << stats.getMachineName() << "\",";
    logger->info(nameStream.str());

    std::stringstream mtbfStream;
    mtbfStream << "\t\t\t\t\"MTBFinHours\" : " << stats.getMTBFinHours() << ",";
    logger->info(mtbfStream.str());

    std::stringstream timesBrokenStream;
    timesBrokenStream << "\t\t\t\t\"totalTimesBroken\" : " << stats.getTimesBroken() << ",";
    logger->info(timesBrokenStream.str());

    std::stringstream totalDownTimeStream;
    totalDownTimeStream << "\t\t\t\t\"totalDownTime\" : " << stats.getTotalDownTime() << ",";
    logger->info(totalDownTimeStream.str());

    logger->info("\t\t\t\t\"products\" :");
    logger->info("\t\t\t\t[");

    bool firstProduct = true;

    for (auto &product : stats.getProductStatistics()) {

      if (product.getId() != 0) {

        if (!firstProduct) {
          logger->info("\t\t\t\t\t},");
        }

        logger->info("\t\t\t\t\t{");
        firstProduct = false;

        std::stringstream productIdStream;
        productIdStream << "\t\t\t\t\t\t\"productId\" : " << product.getId() << ",";
        logger->info(productIdStream.str());

        std::stringstream totalProducedStream;
        totalProducedStream << "\t\t\t\t\t\t\"totalProduced\" : " << product.getTotalProduced() << ",";
        logger->info(totalProducedStream.str());

        std::stringstream avgProducedStream;
        avgProducedStream << "\t\t\t\t\t\t\"avgProduced\" : " << product.getAvgProduced() << ",";
        logger->info(avgProducedStream.str());

        std::stringstream totalLostStream;
        totalLostStream << "\t\t\t\t\t\t\"totalLost\" : " << product.getTotalLost() << ",";
        logger->info(totalLostStream.str());

        std::stringstream avgLostStream;
        avgLostStream << "\t\t\t\t\t\t\"avgLost\" : " << product.getAvgLost() << ",";
        logger->info(avgLostStream.str());

        std::stringstream avgProductionTimeStream;
        avgProductionTimeStream << "\t\t\t\t\t\t\"avgProductionTime\" : " << product.getAvgProductionTime() << ",";
        logger->info(avgProductionTimeStream.str());

        std::stringstream avgIdleTimeStream;
        avgIdleTimeStream << "\t\t\t\t\t\t\"avgIdleTime\" : " << product.getAvgIdleTime() << ",";
        logger->info(avgIdleTimeStream.str());

        std::stringstream avgDownTimeStream;
        avgDownTimeStream << "\t\t\t\t\t\t\"avgDownTime\" : " << product.getAvgDownTime() << ",";
        logger->info(avgDownTimeStream.str());

        std::stringstream avgConfigureTimeStream;
        avgConfigureTimeStream << "\t\t\t\t\t\t\"avgConfigureTime\" : " << product.getAvgConfigureTime();
        logger->info(avgConfigureTimeStream.str());

      }
    }
    if(!stats.getProductStatistics().empty()) {
      logger->info("\t\t\t\t\t}");
    }
    logger->info("\t\t\t\t]");

  }
  logger->info("\t\t\t}");
  logger->info("\t\t]");
  logger->info("\t}");
}

}