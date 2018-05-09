//
// Created by klei on 4/25/18.
//

#ifndef PRODUCTION_LINE_CONTROL_CONTROLLERSTATE_H
#define PRODUCTION_LINE_CONTROL_CONTROLLERSTATE_H

#include "../SimulationController.h"

namespace States {

	enum EventType {
		kEventTypeReadConfigFile,
		kEventTypeSimulationConfigLoaded,
		kEventTypeProductionConfigLoaded,
		kEventTypeServerSetupFailed,
		kEventTypeMachineConnected,
		kEventTypeAllMachinesReadyForSimulation,
		kEventTypeMachineReady,
//		kEventType,
//		kEventType,
	};

	typedef Patterns::Statemachine::Event Event;
	typedef Patterns::Statemachine::EventPtr EventPtr;

	class ControllerState : public Patterns::Statemachine::State {

	public:
		virtual ~ControllerState() = default;
		virtual bool handleEvent(const EventPtr &e) override;
		virtual void entryAction() = 0;
		virtual void doActivity() = 0;
		virtual void exitAction() = 0;

	protected:
		ControllerState(Simulation::SimulationController &);
		Simulation::SimulationController& context;

	};

}


#endif //PRODUCTION_LINE_CONTROL_CONTROLLERSTATE_H
