//
// Created by don on 28-5-18.
//

#include "ReadState.h"
void filestates::ReadState::doActivity() {

}
void filestates::ReadState::entryAction() {

}
void filestates::ReadState::exitAction() {

}
bool filestates::ReadState::handleEvent(const patterns::statemachine::EventPtr &e) {
  return FileState::handleEvent(e);
}
