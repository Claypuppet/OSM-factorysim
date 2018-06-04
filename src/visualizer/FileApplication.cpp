//
// Created by don on 28-5-18.
//

#include <utils/Logger.h>
#include "FileApplication.h"
#include "application_states/file_states/ReadState.h"

namespace file {

bool FileApplication::loadResults(const std::string &filePath) {
  utils::Logger::log(__PRETTY_FUNCTION__);
  if (!fileReader.deserializeEvents(filePath, productionEvents)) {
    auto event = std::make_shared<patterns::statemachine::Event>(filestates::StateEventTypes::eFailedReading);
    scheduleEvent(event);
    return false;
  }

  configuration = fileReader.deserializeSimConfig(filePath);

  if (!configuration) {
    auto event = std::make_shared<patterns::statemachine::Event>(filestates::StateEventTypes::eFailedReading);
    scheduleEvent(event);
    return false;
  }

  for (const auto &machine : configuration->getProductionLine()->getMachines()) {
    machines.push_back(std::make_shared<visualisercore::Machine>(*machine));
  }

  if(machines.size() == 0){
    auto event = std::make_shared<patterns::statemachine::Event>(filestates::StateEventTypes::eFailedReading);
    scheduleEvent(event);
    return false;
  }

  std::stringstream logMessage;
  logMessage << "Loaded " << productionEvents.size() << " events!";
  utils::Logger::log(logMessage.str());

  auto event = std::make_shared<patterns::statemachine::Event>(filestates::StateEventTypes::eDoneReading);
  scheduleEvent(event);

  return true;
}

const std::string &FileApplication::getPathToFile() const {
  return pathToFile;
}

void FileApplication::setPathToFile(const std::string &pathToAFile) {
  pathToFile = pathToAFile;
}

void FileApplication::setStartState() {
  setCurrentState(std::make_shared<filestates::ReadState>(*this));
}

FileApplication::FileApplication(const std::string &pathToAFile)
    : pathToFile(pathToAFile) {
}

}
