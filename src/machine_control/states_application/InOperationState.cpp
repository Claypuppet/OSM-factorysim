//
// Created by hqnders on 24/05/18.
//

#include "InOperationState.h"

#include <utils/Logger.h>
#include "IdleState.h"
#include "BrokenState.h"
#include "../states_machine/InOperation/TakeProductState.h"

namespace applicationstates {

InOperationState::InOperationState(machinecore::Application &aContext) : ApplicationState(aContext) {

};

void InOperationState::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);

  auto state = std::make_shared<machinestates::TakeProductState>(*context.getMachine());
  context.getMachine()->setCurrentState(state);
}

void InOperationState::doActivity() {
  context.getMachine()->run();
}

void InOperationState::exitAction() {

}

bool InOperationState::handleEvent(const applicationstates::EventPtr &event) {
  switch (event->getId()) {
    case kEventTypeFinishedProcessing: {
      onFinishedProcessing();
    }

    case kEventTypeMachineBroke: {
      onMachineBroke();
    }

    default: {
      return ApplicationState::handleEvent(event);
    }
  }
}

void InOperationState::onFinishedProcessing() {
  utils::Logger::log("-Handle event: kEventTypeFinishedProcessing");

  //Notify controller?
  auto state = std::make_shared<IdleState>(context);
  context.setCurrentState(state);
}

void InOperationState::onMachineBroke() {
  utils::Logger::log("-Handle event: kEventTypeMachineBroke");

  auto state = std::make_shared<BrokenState>(context);
  context.setCurrentState(state);
}
} // applicationstates
