//
// Created by don on 28-5-18.
//

#include "FileApplication.h"
#include "application_states/file_states/ReadState.h"

namespace file {

bool FileApplication::loadResults(const std::string &filePath) {

  if (!fileReader.deserializeEvents(filePath, productionEvents)) {
    return false;
  }

  configuration = fileReader.deserializeSimConfig(filePath);

  for (auto &machine : configuration->getProductionLine()->getMachines()) {
    machines.push_back(std::make_shared<visualisercore::Machine>(*machine));
  }

  for(auto &event : productionEvents)
  {
    std::cout << event->toString() << std::endl;
  }

  return true;
}

const std::string &FileApplication::getPathToFile() const {
  return pathToFile;
}

void FileApplication::setPathToFile(const std::string &pathToAFile) {
  pathToFile = pathToAFile;
}

void FileApplication::setStartState() {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  setCurrentState(std::make_shared<filestates::ReadState>(*this));
}

FileApplication::FileApplication(const std::string &pathToAFile)
    : pathToFile(pathToAFile) {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void FileApplication::run() {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  Context::run();
}

}
