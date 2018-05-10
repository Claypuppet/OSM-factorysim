//
// Created by sven on 23-4-18.
//

#include "BrokenState.h"

namespace ProductionStates {
BrokenState::BrokenState(machinecore::Application &aContext)
    : ProductionState(aContext) {

}

void BrokenState::entryAction() {

}

void BrokenState::doActivity() {

}

void BrokenState::exitAction() {

}
bool BrokenState::handleEvent(const Patterns::Statemachine::EventPtr &e) {
  return false;
}

}
