//
// Created by don on 28-5-18.
//

#include "FileFeedState.h"

namespace mainwindowstates {

void FileFeedState::doActivity() {

}
void FileFeedState::entryAction() {

}
void FileFeedState::exitAction() {

}
bool FileFeedState::handleEvent(const patterns::statemachine::EventPtr &event) {
  return MainWindowState::handleEvent(event);
}

}
