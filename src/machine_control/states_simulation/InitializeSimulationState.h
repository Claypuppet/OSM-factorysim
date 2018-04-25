//
// Created by klei on 4/23/18.
//

#ifndef PRODUCTION_LINE_CONTROL_INITIALIZESIMULATIONSTATE_H
#define PRODUCTION_LINE_CONTROL_INITIALIZESIMULATIONSTATE_H

#include "SimulationState.h"

namespace SimulationStates {


	class InitializeSimulationState : public SimulationState {
	public:
		InitializeSimulationState(Simulator::SimulationController &context) : SimulationState(context){};
		virtual ~InitializeSimulationState() = default;

		void entryAction() override;

		void doActivity() override;

		void exitAction() override;

		bool handleEvent(const EventPtr &e) override;

	};

}

#endif //PRODUCTION_LINE_CONTROL_INITIALIZESIMULATIONSTATE_H
