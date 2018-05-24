//
// Created by hqnders on 24/05/18.
//

#include "ReadyingConfigState.h"

#include <utils/Logger.h>
#include "ConfiguringState.h"

namespace machinestates {

ReadyingConfigState::ReadyingConfigState(machinecore::Machine &aContext) : MachineState(aContext) {
  utils::Logger::log(__PRETTY_FUNCTION__);
}

void ReadyingConfigState::entryAction() {

}

void ReadyingConfigState::doActivity() {

}

void ReadyingConfigState::exitAction() {

}

bool ReadyingConfigState::handleEvent(const machinestates::EventPtr &event) {
  switch(event->getId()) {
    case kEventTypeReconfigure: {
      onReconfigure(event);
      return true;
    }

    default: {
      return MachineState::handleEvent(event);
    }
  }
}

void ReadyingConfigState::onReconfigure(const EventPtr &event) {
  utils::Logger::log("-Handle event: kEventTypeReconfigure");

  auto nextConfig = context.getConfigurations().at(event->getArgumentAsType<uint32_t>());
  context.setCurrentConfiguration(nextConfig);

  auto state = std::make_shared<ConfiguringState>(context);
  context.setCurrentState(state);
}
} // machinestates