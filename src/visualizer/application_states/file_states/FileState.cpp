//
// Created by don on 28-5-18.
//

#include "FileState.h"
#include "PlayState.h"
#include "FileConfigureState.h"

namespace filestates {

bool FileState::handleEvent(const patterns::statemachine::EventPtr &event) {
  switch(event->getId())
  {
    case StateEventTypes::eDoneReading:
      context.setCurrentState(std::make_shared<FileConfigureState>());
      break;
    case StateEventTypes::eDoneConfiguring:
      context.setCurrentState(std::make_shared<PlayState>());
      break;
  }
  return false;
}

FileState::FileState(file::FileApplication &application)
    : context(application) {
}

}
