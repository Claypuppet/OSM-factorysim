/*
 * Context.cpp
 *
 *  Created on: 5 mrt. 2018
 *      Author: henri
 */
#include "Context.h"

patterns::statemachine::Context::Context() {
}

patterns::statemachine::Context::~Context() {
}

void patterns::statemachine::Context::setCurrentState(const std::shared_ptr<State> currentState) {
	if(this->currentState){
		this->currentState->exitAction();
	}

	this->currentState = currentState;

	this->currentState->entryAction();
	this->currentState->doActivity();
}

void patterns::statemachine::Context::scheduleEvent(Event e){
	events.push(e);
}

void patterns::statemachine::Context::run(){
	while(!events.empty()){
		if(!currentState->handleEvent(events.front(), *this)){
		}
		events.pop();
	}
}
