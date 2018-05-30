//
// Created by don on 28-5-18.
//

#include "NeutralState.h"

namespace mainwindowstates {

void NeutralState::doActivity() {

}
void NeutralState::entryAction() {

}
void NeutralState::exitAction() {

}
bool NeutralState::handleEvent(const patterns::statemachine::EventPtr &event) {
  return MainWindowState::handleEvent(event);
}

}
