//
// Created by klei on 4/23/18.
//

#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONSTATE_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONSTATE_H

#include <patterns/statemachine/State.h>
#include "../SimulationNetworkComponent.h"

namespace SimulationStates {

	class SimulationState : Patterns::Statemachine::State {

	public:
		virtual ~SimulationState() = default;
		virtual void entryAction() = 0;
		virtual void doActivity() = 0;
		virtual void exitAction() = 0;
	protected:
		SimulationState(SimulationCommunication::SimulationNetworkComponent&);
		SimulationCommunication::SimulationNetworkComponent& context;

	};
}


#endif //PRODUCTION_LINE_CONTROL_SIMULATIONSTATE_H
