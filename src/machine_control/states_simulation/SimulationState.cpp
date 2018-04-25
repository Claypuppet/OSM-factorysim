//
// Created by klei on 4/23/18.
//

#include "SimulationState.h"

namespace SimulationStates {

	SimulationState::SimulationState(Simulator::SimulationController &aContext)
		: context(aContext){

	}

	bool SimulationState::handleEvent(const EventPtr &e) {
		switch(e->getId()){
			default:
				return false;
		}
	}

}
