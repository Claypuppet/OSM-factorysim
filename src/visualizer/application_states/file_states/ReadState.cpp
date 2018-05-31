//
// Created by don on 28-5-18.
//

#include "ReadState.h"

namespace filestates {

void ReadState::doActivity() {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  context.loadResults(context.getPathToFile());

  auto event = std::make_shared<patterns::statemachine::Event>(StateEventTypes::eDoneReading);
  context.scheduleEvent(event);
}

void ReadState::entryAction() {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void ReadState::exitAction() {

}

bool ReadState::handleEvent(const patterns::statemachine::EventPtr &event) {
  return FileState::handleEvent(event);
}

ReadState::ReadState(file::FileApplication &application) : FileState(application) {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

}
