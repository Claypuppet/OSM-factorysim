//
// Created by don on 28-5-18.
//

#include "FileConfigureState.h"

namespace filestates{

void FileConfigureState::doActivity() {

}
void FileConfigureState::entryAction() {

}
void FileConfigureState::exitAction() {

}
bool FileConfigureState::handleEvent(const patterns::statemachine::EventPtr &event) {
  return FileState::handleEvent(event);
}

}
