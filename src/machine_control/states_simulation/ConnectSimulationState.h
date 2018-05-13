//
// Created by klei on 4/23/18.
//

#ifndef PRODUCTION_LINE_CONTROL_CONNECTSIMULATIONSTATE_H
#define PRODUCTION_LINE_CONTROL_CONNECTSIMULATIONSTATE_H

#include "SimulationState.h"

namespace simulationstates {


	class ConnectSimulationState : public SimulationState {
	public:
		ConnectSimulationState(simulator::SimulationController &context) : SimulationState(context){};
		virtual ~ConnectSimulationState() = default;

		void entryAction() override;

		void doActivity() override;

		void exitAction() override;

		bool handleEvent(const EventPtr &e) override;

	};

}

#endif //PRODUCTION_LINE_CONTROL_INITIALIZESIMULATIONSTATE_H
