//
// Created by don on 28-5-18.
//

#include <utils/Logger.h>
#include "ReadState.h"
#include "FileConfigureState.h"

namespace filestates {

void ReadState::doActivity() {
  utils::Logger::log(__PRETTY_FUNCTION__);
  context.loadResults(context.getPathToFile());
}

void ReadState::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);
}

void ReadState::exitAction() {

}

ReadState::ReadState(file::FileApplication &application) : FileState(application) {
}
bool ReadState::handleEvent(const patterns::statemachine::EventPtr &event) {
  switch(event->getId()) {
    case StateEventTypes::eDoneReading:
      context.setCurrentState(std::make_shared<FileConfigureState>(context));
      return true;
    case StateEventTypes::eFailedReading:
      context.setCurrentState(nullptr);
      std::cerr << "Error: Invalid file!" << std::endl;
      return true;
    default:
      return false;
  }
}

}
