//
// Created by don on 28-5-18.
//

#include <utils/Logger.h>
#include "ReadState.h"

namespace filestates {

void ReadState::doActivity() {
  utils::Logger::log(__PRETTY_FUNCTION__);
  if (!context.loadResults(context.getPathToFile())) {
    std::cout << "Failed loading result file";
    return;
  }
  auto event = std::make_shared<patterns::statemachine::Event>(StateEventTypes::eDoneReading);
  context.scheduleEvent(event);
}

void ReadState::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);
}

void ReadState::exitAction() {

}

ReadState::ReadState(file::FileApplication &application) : FileState(application) {
}

}
