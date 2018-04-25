//
// Created by klei on 4/23/18.
//

#ifndef PRODUCTION_LINE_CONTROL_SHUTDOWNSTATE_H
#define PRODUCTION_LINE_CONTROL_SHUTDOWNSTATE_H

#include "SimulationState.h"


namespace SimulationStates {


	class ShutdownState : public SimulationState {
	public:
		ShutdownState(SimulationCommunication::SimulationNetworkComponent &context) : SimulationState(context){};
		virtual ~ShutdownState() = default;

		void entryAction() override;

		void doActivity() override;

		void exitAction() override;

	};

}
#endif //PRODUCTION_LINE_CONTROL_SHUTDOWNSTATE_H