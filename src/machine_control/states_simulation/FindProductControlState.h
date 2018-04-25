//
// Created by klei on 4/24/18.
//

#ifndef PRODUCTION_LINE_CONTROL_FINDPRODUCTCONTROLSTATE_H
#define PRODUCTION_LINE_CONTROL_FINDPRODUCTCONTROLSTATE_H

#include "SimulationState.h"

namespace SimulationStates {


	class FindProductControlState : public SimulationState {
	public:
		FindProductControlState(Simulator::SimulationController &context) : SimulationState(context){};
		virtual ~FindProductControlState() = default;

		void entryAction() override;

		void doActivity() override;

		void exitAction() override;

		bool handleEvent(const EventPtr &e) override;

	};

}



#endif //PRODUCTION_LINE_CONTROL_FINDPRODUCTCONTROLSTATE_H
