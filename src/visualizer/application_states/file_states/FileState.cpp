//
// Created by don on 28-5-18.
//

#include "FileState.h"
#include "PlayState.h"
#include "FileConfigureState.h"

namespace filestates {

FileState::FileState(file::FileApplication &application)
    : context(application) {
}
bool FileState::handleEvent(const patterns::statemachine::EventPtr &e) {
  return false;
}

}
