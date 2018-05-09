/*
 * Context.cpp
 *
 *  Created on: 5 mrt. 2018
 *      Author: henri
 */
#include "Context.h"

void Patterns::Statemachine::Context::setCurrentState(const StatePtr newState) {
	if(currentState){
		currentState->exitAction();
	}

	currentState = newState;

	currentState->entryAction();
	currentState->doActivity();
}

void Patterns::Statemachine::Context::scheduleEvent(EventPtr e){
	events.push(e);
}

void Patterns::Statemachine::Context::run(){
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
const Patterns::Statemachine::StatePtr &Patterns::Statemachine::Context::getCurrentState() const {
  return currentState;
}
