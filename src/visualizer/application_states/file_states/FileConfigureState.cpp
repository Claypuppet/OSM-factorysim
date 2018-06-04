//
// Created by don on 28-5-18.
//

#include <utils/Logger.h>
#include "FileConfigureState.h"
#include "PlayState.h"

namespace filestates {

void FileConfigureState::doActivity() {
  utils::Logger::log(__PRETTY_FUNCTION__);
  /*
   * TODO configure
   */
  auto event = std::make_shared<patterns::statemachine::Event>(StateEventTypes::eDoneConfiguring);
  context.scheduleEvent(event);
}

void FileConfigureState::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);
}

void FileConfigureState::exitAction() {

}

FileConfigureState::FileConfigureState(file::FileApplication &application)
    : FileState(application) {

}
bool FileConfigureState::handleEvent(const patterns::statemachine::EventPtr &event) {
  switch(event->getId())
  {
    case StateEventTypes::eDoneConfiguring:
      context.setCurrentState(std::make_shared<PlayState>(context));
      return true;
    default:
      return false;
  }
}

}
