//
// Created by don on 28-5-18.
//

#include "ReadState.h"

namespace filestates {

void ReadState::doActivity() {

}
void ReadState::entryAction() {

}
void ReadState::exitAction() {

}
bool ReadState::handleEvent(const patterns::statemachine::EventPtr &event) {
  return FileState::handleEvent(event);
}

}
