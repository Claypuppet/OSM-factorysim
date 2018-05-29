//
// Created by don on 28-5-18.
//

#include "FileConfigureState.h"
void filestates::FileConfigureState::doActivity() {

}
void filestates::FileConfigureState::entryAction() {

}
void filestates::FileConfigureState::exitAction() {

}
bool filestates::FileConfigureState::handleEvent(const patterns::statemachine::EventPtr &event) {
  return FileState::handleEvent(event);
}
