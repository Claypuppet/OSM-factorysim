//
// Created by don on 28-5-18.
//

#include "PlayState.h"
void filestates::PlayState::doActivity() {

}
void filestates::PlayState::entryAction() {

}
void filestates::PlayState::exitAction() {

}
bool filestates::PlayState::handleEvent(const patterns::statemachine::EventPtr &event) {
  return FileState::handleEvent(event);
}
