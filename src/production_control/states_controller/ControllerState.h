
#ifndef PRODUCTION_LINE_CONTROL_CONTROLLERSTATE_H
#define PRODUCTION_LINE_CONTROL_CONTROLLERSTATE_H

#include "../SimulationController.h"

namespace states {

	enum EventType {
		kEventTypeReadConfigFile,
		kEventTypeSimulationConfigLoaded,
		kEventTypeProductionConfigLoaded,
		kEventTypeServerSetupFailed,
		kEventTypeMachineConnected,
		kEventTypeAllMachinesConnected,
		kEventTypeMachineReady,
		kEventTypeDoneBroadcasting,
//		kEventType,
	};

	typedef Patterns::Statemachine::Event Event;
	typedef Patterns::Statemachine::EventPtr EventPtr;

	class ControllerState : public Patterns::Statemachine::State {

	public:
		virtual ~ControllerState() = default;
		virtual bool handleEvent(const EventPtr &event) override;
		virtual void entryAction() = 0;
		virtual void doActivity() = 0;
		virtual void exitAction() = 0;

	protected:
		ControllerState(simulation::SimulationController &aContext);
		simulation::SimulationController& context;

	};

}


#endif //PRODUCTION_LINE_CONTROL_CONTROLLERSTATE_H
