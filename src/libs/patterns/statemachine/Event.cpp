/*
 * Event.cpp
 *
 *  Created on: 5 mrt. 2018
 *      Author: henri
 */
#include "Event.h"

Patterns::Statemachine::Event::Event(unsigned long long id)
:id(id){
}

Patterns::Statemachine::Event::Event(const Event& event)
:id(event.id)
{
}

Patterns::Statemachine::Event::~Event() {
}

unsigned long long Patterns::Statemachine::Event::getId() const{
	return id;
}

const Patterns::Statemachine::Event& Patterns::Statemachine::Event::operator=(const Patterns::Statemachine::Event& rhs){
	return rhs;
}
