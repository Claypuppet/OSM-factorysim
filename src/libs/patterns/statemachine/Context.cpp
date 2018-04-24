/*
 * Context.cpp
 *
 *  Created on: 5 mrt. 2018
 *      Author: henri
 */
#include "Context.h"

Patterns::Statemachine::Context::Context() {
}

Patterns::Statemachine::Context::~Context() {
}

void Patterns::Statemachine::Context::setCurrentState(const std::shared_ptr<State> newState) {
	if(currentState){
		currentState->exitAction();
	}

	currentState = newState;

	currentState->entryAction();
	currentState->doActivity();
}

void Patterns::Statemachine::Context::scheduleEvent(Event e){
	events.push(e);
}

void Patterns::Statemachine::Context::run(){
	while(!events.empty()){
		Event e = events.front();
		events.pop();
		currentState->handleEvent(e, *this);
	}
}
