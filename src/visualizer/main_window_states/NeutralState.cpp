//
// Created by don on 28-5-18.
//

#include "NeutralState.h"
void mainwindowstates::NeutralState::doActivity() {

}
void mainwindowstates::NeutralState::entryAction() {

}
void mainwindowstates::NeutralState::exitAction() {

}
bool mainwindowstates::NeutralState::handleEvent(const patterns::statemachine::EventPtr &e) {
  return MainWindowState::handleEvent(e);
}
