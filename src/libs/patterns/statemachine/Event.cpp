/*
 * Event.cpp
 *
 *  Created on: 5 mrt. 2018
 *      Author: henri
 */
#include "Event.h"

patterns::statemachine::Event::Event(unsigned long long id)
:id(id){
}

patterns::statemachine::Event::Event(const Event& event)
:id(event.id)
{
}

patterns::statemachine::Event::~Event() {
}

unsigned long long patterns::statemachine::Event::getId() const{
	return id;
}

const patterns::statemachine::Event& patterns::statemachine::Event::operator=(const patterns::statemachine::Event& rhs){
	return rhs;
}
