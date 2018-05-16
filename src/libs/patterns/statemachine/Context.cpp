/*
 * Context.cpp
 *
 *  Created on: 5 mrt. 2018
 *      Author: henri
 */
#include "Context.h"

void patterns::statemachine::Context::setCurrentState(const StatePtr newState) {

	if(currentState){
		currentState->exitAction();
	}

	currentState = newState;

	currentState->entryAction();
	currentState->doActivity();
}

void patterns::statemachine::Context::scheduleEvent(EventPtr event) {
  events.push(event);
}

void patterns::statemachine::Context::run() {
	while(!events.empty()) {
		EventPtr e = events.front();
		events.pop();
		auto handled = currentState->handleEvent(e);

		// Re-add unhandled events ?
//		if (!handled){
//			scheduleEvent(e);
//		}
	}
	currentState->doActivity();
}
const patterns::statemachine::StatePtr &patterns::statemachine::Context::getCurrentState() const {
  return currentState;
}
