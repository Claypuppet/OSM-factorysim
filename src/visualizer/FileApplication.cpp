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
    return false;
  }

  configuration = fileReader.deserializeSimConfig(filePath);

  for (auto &machine : configuration->getProductionLine()->getMachines()) {
    machines.push_back(std::make_shared<visualisercore::Machine>(*machine));
  }

  std::stringstream logMessage;
  logMessage << "Loaded " << productionEvents.size() << " events!";
  utils::Logger::log(logMessage.str());

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
