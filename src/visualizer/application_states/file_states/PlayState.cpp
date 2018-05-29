//
// Created by don on 28-5-18.
//

#include "PlayState.h"

namespace filestates {

void PlayState::doActivity() {

}
void PlayState::entryAction() {

}
void PlayState::exitAction() {

}
bool PlayState::handleEvent(const patterns::statemachine::EventPtr &event) {
  return FileState::handleEvent(event);
}

}
