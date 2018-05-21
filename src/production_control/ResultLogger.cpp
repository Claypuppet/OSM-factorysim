//
// Created by sven on 18-5-18.
//

#include <iostream>
#include <sstream>
#include <utils/time/Time.h>
#include <utils/FileLogger.h>
#include "ResultLogger.h"

namespace core {
ResultLogger::ResultLogger()
    : simulationEnabled(true), productionEnabled(true), productionDebug(false), simulationDebug(false) {
  std::cout << "teadlsajjgbvs";
}



void ResultLogger::LogProductionEvent(uint32_t machineId, uint32_t eventId) {
  if (productionEnabled) {
    std::ostringstream stringstream;

    if (!productionDebug) {
      stringstream << "T:" << utils::Time::getInstance().getCurrentTime() << ",MID:" << machineId << ",EID:" << eventId;
      utils::FileLogger::file()->info(stringstream.str());

    } else {
      stringstream << "Time:" << utils::Time::getInstance().getCurrentTime() << ",MachineId:" << machineId;

      switch (eventId) {
        //TODO add switch cases and descriptions for events
        default: {
          stringstream << ",EventId:" << eventId << "-> no description";
          break;
        }
      }
      utils::FileLogger::both()->info(stringstream.str());
    }
  }
}

void ResultLogger::LogSimulationEvent(uint32_t eventId) {
  if (simulationEnabled) {
    //TODO log simulation events
  }
}

void ResultLogger::setSimulationEnabled(bool enabled) {
  getInstance().simulationEnabled = enabled;
}

void ResultLogger::setProductionEnabled(bool enabled) {
  getInstance().productionEnabled = enabled;
}

void ResultLogger::setSimulationDebugOutput(bool enabled) {
  getInstance().simulationDebug = enabled;
}

void ResultLogger::setProductionDebugOutput(bool enabled) {
  getInstance().productionDebug = enabled;
}

}