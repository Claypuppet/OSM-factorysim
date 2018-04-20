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

void Patterns::Statemachine::Context::setCurrentState(const std::shared_ptr<State> currentState) {
	if(this->currentState){
		this->currentState->exitAction();
	}

	this->currentState = currentState;

	this->currentState->entryAction();
	this->currentState->doActivity();
}

void Patterns::Statemachine::Context::scheduleEvent(Event e){
	events.push(e);
}

void Patterns::Statemachine::Context::run(){
	while(!events.empty()){
		if(!currentState->handleEvent(events.front(), *this)){
		}
		events.pop();
	}
}
