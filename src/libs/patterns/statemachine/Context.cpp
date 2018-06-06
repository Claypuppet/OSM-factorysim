/*
 * Context.cpp
 *
 *  Created on: 5 mrt. 2018
 *      Author: henri
 */
#include "Context.h"

void patterns::statemachine::Context::setCurrentState(const StatePtr newState) {

  if (currentState) {
	currentState->exitAction();
  }

  currentState = newState;

  currentState->entryAction();
}

void patterns::statemachine::Context::scheduleEvent(EventPtr event) {
  events.push(event);
}

void patterns::statemachine::Context::run() {
  currentState->doActivity();
  while (!events.empty()) {
	EventPtr &event = events.front();
	currentState->handleEvent(event);
    events.pop();
  }
}
const patterns::statemachine::StatePtr &patterns::statemachine::Context::getCurrentState() const {
  return currentState;
}
