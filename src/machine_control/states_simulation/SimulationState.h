//
// Created by klei on 4/23/18.
//

#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONSTATE_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONSTATE_H

#include <patterns/statemachine/State.h>
#include "../SimulationNetworkComponent.h"
#include "Event.h"

namespace SimulationStates {

	class SimulationState : Patterns::Statemachine::State {

	public:
		virtual ~SimulationState() = default;
		virtual bool handleEvent(const Event &e, SimulationCommunication::SimulationNetworkComponent &c) {};
		virtual void entryAction() {};
		virtual void doActivity() {};
		virtual void exitAction() {};
	protected:
		SimulationState(SimulationCommunication::SimulationNetworkComponent&);
		SimulationCommunication::SimulationNetworkComponent& context;

	};
}


#endif //PRODUCTION_LINE_CONTROL_SIMULATIONSTATE_H
