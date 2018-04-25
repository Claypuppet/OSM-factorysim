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
		kEventTypeAllMachinesConnected,
		kEventTypeMachineReady,
//		kEventType,
//		kEventType,
	};

	typedef Patterns::Statemachine::Event Event;
	typedef Patterns::Statemachine::EventPtr EventPtr;

	class ControllerState : public Patterns::Statemachine::State {

	public:
		virtual ~ControllerState() = default;
		virtual bool handleEvent(const EventPtr &e);
		virtual void entryAction() = 0;
		virtual void doActivity() = 0;
		virtual void exitAction() = 0;
	protected:
		ControllerState(Core::SimulationController &);
		Core::SimulationController& context;

	};

}


#endif //PRODUCTION_LINE_CONTROL_CONTROLLERSTATE_H
