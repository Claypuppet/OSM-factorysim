//
// Created by klei on 4/23/18.
//

#ifndef PRODUCTION_LINE_CONTROL_EVENT_H
#define PRODUCTION_LINE_CONTROL_EVENT_H

#include <patterns/statemachine/Event.h>
#include <cstdint>

namespace SimulationStates {

	class Event : public Patterns::Statemachine::Event {
	public:
		Event(uint32_t id);


	};
}


#endif //PRODUCTION_LINE_CONTROL_EVENT_H
