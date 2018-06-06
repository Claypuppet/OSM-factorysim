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
    utils::FileLogger::getInstance().logToBoth(logRow.str());
  }
  else {
    utils::FileLogger::getInstance().logToFile(logRow.str());
  }
  // Temp here till we have a production shutdown.
  utils::FileLogger::getInstance().flushLoggers();
}
void ResultLogger::logStatistics(const std::vector<MachinePtr> &machines) {
  std::string outputFileName = "./statistics.json";

  auto &logger = utils::FileLogger::i();

  logger.setupLogger(outputFileName, true);

  logger.logToFile("{");
  logWeeklyStatistics(machines);
  logAverageStatistics(machines);
  logger.logToFile("}");

}

void ResultLogger::logWeeklyStatistics(const std::vector<MachinePtr> &machines) {
  auto &logger = utils::FileLogger::getInstance();

  logger.logToFile("\t\"weeks\":\n\t[");
  auto weeks = static_cast<uint16_t>(machines[0]->getWeeklyStatistics().size());

  for (uint16_t i = 0; i < weeks; ++i) {
    logger.logToFile("\t\t{");
    std::stringstream weekInfo;
    weekInfo << "\t\t\t\"week\" : " << i + 1 << ",";
    logger.logToFile(weekInfo.str());
    logger.logToFile("\t\t\t\"machines\" : [");
    for (auto &machine : machines) {
      if (machine->getWeeklyStatistics().size() > i) {
        auto weekStats = machine->getWeeklyStatistics()[i];
        logger.logToFile("\t\t\t\t{");

        std::stringstream idInfo;
        idInfo << "\t\t\t\t\t\"id\" : " << machine->getId() << ",";
        logger.logToFile(idInfo.str());

        std::stringstream producedProducts;
        producedProducts << "\t\t\t\t\t\"producedProducts\" : {";
        for (auto &item : weekStats.getProducedProducts()) {
          producedProducts << "\"" << item.first << "\"" <<":" << item.second << ",";
        }
        producedProducts << "},";
        logger.logToFile(producedProducts.str());

        std::stringstream lostProducts;
        lostProducts << "\t\t\t\t\t\"lostProducts\" : {";
        for (auto &item : weekStats.getLostProducts()) {
          lostProducts <<  "\"" << item.first << "\"" <<":" << item.second << ",";
        }
        lostProducts << "},";
        logger.logToFile(lostProducts.str());

        std::stringstream downTime;
        downTime << "\t\t\t\t\t\"downTime\" : " << weekStats.getDownTime() << ",";
        logger.logToFile(downTime.str());

        std::stringstream productionTime;
        productionTime << "\t\t\t\t\t\"productionTime\" : " << weekStats.getProductionTime() << ",";
        logger.logToFile(productionTime.str());

        std::stringstream idleTime;
        idleTime << "\t\t\t\t\t\"idleTime\" : " << weekStats.getIdleTime() << ",";
        logger.logToFile(idleTime.str());

        std::stringstream configureTime;
        configureTime << "\t\t\t\t\t\"configureTime\" : " << weekStats.getConfigureTime();
        logger.logToFile(configureTime.str());

        logger.logToFile("\t\t\t\t},");
      }
    }
    logger.logToFile("\t\t\t]");
    logger.logToFile("\t\t},");
  }
  logger.logToFile("\t]");
}

void ResultLogger::logAverageStatistics(const std::vector<MachinePtr> &machines) {
  auto &logger = utils::FileLogger::getInstance();

  logger.logToFile("\t\"Average\":{");
  logger.logToFile("\t\t\"Machines\":");
  logger.logToFile("\t\t[");
  for(auto &machine : machines){

    auto nWeeks = static_cast<uint16_t>(machine->getWeeklyStatistics().size());
    if(nWeeks == 0){
      break;
    }

    logger.logToFile("\t\t\t{");

    std::stringstream idStream;
    idStream << "\t\t\t\t\"id\" : " << machine->getId() << ",";
    logger.logToFile(idStream.str());

    auto weeklyStats = machine->getWeeklyStatistics();

    std::map<uint16_t, uint16_t> totalProduced;
    std::map<uint16_t, uint16_t> totalLost;
    uint64_t totalProductionTime = 0;
    uint64_t totalIdleTime = 0;
    uint64_t totalDownTime = 0;
    uint64_t totalConfigureTime = 0;

    for(auto &weekStats : weeklyStats){
      for(auto &item : weekStats.getProducedProducts()){
        totalProduced[item.first] += item.second;
      }
      for(auto &item : weekStats.getLostProducts()){
        totalLost[item.first] += item.second;
      }
      totalProductionTime += weekStats.getProductionTime();
      totalIdleTime += weekStats.getIdleTime();
      totalDownTime += weekStats.getDownTime();
      totalConfigureTime += weekStats.getConfigureTime();
    }

    std::stringstream producedStream;
    producedStream << "\t\t\t\t\"producedProducts\" : {";
    for(auto& item : totalProduced){
      producedStream << "\"" << item.first << "\":" << item.second / nWeeks << ",";
    }
    producedStream << "},";
    logger.logToFile(producedStream.str());

    std::stringstream lostStream;
    lostStream << "\t\t\t\t\"lostProducts\" : {";
    for(auto& item : totalLost){
      producedStream << "\"" << item.first << "\":" << item.second / nWeeks << ",";
    }
    lostStream << "},";
    logger.logToFile(lostStream.str());

    std::stringstream productionStream;
    productionStream << "\t\t\t\t\"productionTime\" : " << totalProductionTime / nWeeks << ",";
    logger.logToFile(productionStream.str());

    std::stringstream idleStream;
    idleStream << "\t\t\t\t\"idleTime\" : " << totalIdleTime / nWeeks << ",";
    logger.logToFile(idleStream.str());

    std::stringstream downTimeStream;
    downTimeStream << "\t\t\t\t\"downTime\" : " << totalDownTime / nWeeks << ",";
    logger.logToFile(downTimeStream.str());

    std::stringstream configureStream;
    configureStream << "\t\t\t\t\"configureTime\" : " << totalConfigureTime / nWeeks << ",";
    logger.logToFile(configureStream.str());

    std::stringstream mtbfStream;
    mtbfStream << "\t\t\t\t\"mtbf\" : " << machine->getMTBF();
    logger.logToFile(mtbfStream.str());

    logger.logToFile("\t\t\t}");
  }
  logger.logToFile("\t\t]");
  logger.logToFile("\t}");
}

}