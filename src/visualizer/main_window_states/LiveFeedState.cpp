//
// Created by don on 28-5-18.
//

#include "LiveFeedState.h"

namespace mainwindowstates {

void LiveFeedState::doActivity() {

}
void LiveFeedState::entryAction() {

}
void LiveFeedState::exitAction() {

}
bool LiveFeedState::handleEvent(const patterns::statemachine::EventPtr &event) {
  return MainWindowState::handleEvent(event);
}

}