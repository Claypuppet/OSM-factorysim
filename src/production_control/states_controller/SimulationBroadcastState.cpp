//
// Created by don on 24-4-18.
//

#include <utils/Logger.h>
#include "SimulationBroadcastState.h"
#include "SimulationWaitForConnectionsState.h"

states::SimulationBroadcastState::SimulationBroadcastState(simulation::SimulationController &context) :
	ControllerState(context) {
}

void states::SimulationBroadcastState::doActivity() {

  // temp move directly to next state
  states::EventPtr event = std::make_shared<states::Event>(states::EventType::kEventTypeDoneBroadcasting);
  context.scheduleEvent(event);
}

void states::SimulationBroadcastState::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);
  // TODO: start UDP server
}

void states::SimulationBroadcastState::exitAction() {

}

bool states::SimulationBroadcastState::handleEvent(const EventPtr &e) {
  switch (e->getId()) {
	case states::EventType::kEventTypeDoneBroadcasting:
	  utils::Logger::log("-Handle event: kEventTypeDoneBroadcasting");
	  context.setCurrentState(std::make_shared<states::SimulationWaitForConnectionsState>(context));
	  return true;
  }
  return false;
}
