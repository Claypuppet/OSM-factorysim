//
// Created by don on 28-5-18.
//

#include "FileConfigureState.h"

namespace filestates {

void FileConfigureState::doActivity() {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void FileConfigureState::entryAction() {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void FileConfigureState::exitAction() {

}

bool FileConfigureState::handleEvent(const patterns::statemachine::EventPtr &event) {
  return FileState::handleEvent(event);
}

FileConfigureState::FileConfigureState(file::FileApplication &application)
    : FileState(application) {

}

}
