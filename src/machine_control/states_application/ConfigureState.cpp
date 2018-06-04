//
// Created by hqnders on 23/05/18.
//

#include "ConfigureState.h"

#include "IdleState.h"
#include "BrokenState.h"
#include "../states_machine/Configure/ConfiguringState.h"
#include <utils/Logger.h>

namespace applicationstates {

ConfigureState::ConfigureState(machinecore::Application &aContext) : ApplicationState(aContext) {

}

void ConfigureState::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);
  context.statusUpdate(models::Machine::kMachineStatusConfiguring);

  auto event = std::make_shared<machinestates::Event>(machinestates::kEventTypeReconfigure);
  event->addArgument<uint16_t>(context.getConfigToSet());
  context.getMachine()->scheduleEvent(event);

  context.getMachine()->setConfigureStartState();
}

void ConfigureState::doActivity() {
  context.getMachine()->run();
}

void ConfigureState::exitAction() {

}

bool ConfigureState::handleEvent(const applicationstates::EventPtr &event) {
  switch (event->getId()) {
    case kEventTypeConfigured: {
      onConfigured();
      return true;
    }

    case kEventTypeFailedToConfigure: {
      onFailedToConfigure();
      return true;
    }

    case kEventTypeMachineBroke: {
      onMachineBroke();
      return true;
    }

    default: {
      return ApplicationState::handleEvent(event);
    }
  }
}

void ConfigureState::onConfigured() {
  utils::Logger::log("-Handle event: kEventTypeConfigured");

  auto state = std::make_shared<IdleState>(context);
  context.setCurrentState(state);
}

void ConfigureState::onFailedToConfigure() {
  utils::Logger::log("-Handle event: kEventTypeFailedToConfigure");

  auto state = std::make_shared<BrokenState>(context);
  context.setCurrentState(state);
}

void ConfigureState::onMachineBroke() {
  utils::Logger::log("-Handle event: kEventTypeMachineBroke");

  auto state = std::make_shared<BrokenState>(context);
  context.setCurrentState(state);
}
} // applicationstates
