//
// Created by klei on 4/23/18.
//

#ifndef PRODUCTION_LINE_CONTROL_INITIALIZESIMULATIONSTATE_H
#define PRODUCTION_LINE_CONTROL_INITIALIZESIMULATIONSTATE_H

#include "SimulationState.h"

namespace SimulationStates {


	class InitializeSimulationState : public SimulationState {
		InitializeSimulationState(SimulationCommunication::SimulationNetworkComponent &context) : SimulationState(context){};
		virtual ~InitializeSimulationState() = default;

	public:
		void entryAction() override;

		void doActivity() override;

		void exitAction() override;

	};

}

#endif //PRODUCTION_LINE_CONTROL_INITIALIZESIMULATIONSTATE_H
