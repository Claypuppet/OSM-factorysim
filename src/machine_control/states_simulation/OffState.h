//
// Created by klei on 4/23/18.
//

#ifndef PRODUCTION_LINE_CONTROL_OFFSTATE_H
#define PRODUCTION_LINE_CONTROL_OFFSTATE_H

#include "SimulationState.h"


namespace SimulationStates {


	class OffState : public SimulationState {
	public:
		OffState(Simulator::SimulationController &context) : SimulationState(context){};
		virtual ~OffState() = default;

		void entryAction() override;

		void doActivity() override;

		void exitAction() override;

		bool handleEvent(const EventPtr &e) override;

	};

}

#endif //PRODUCTION_LINE_CONTROL_OFFSTATE_H
