//
// Created by hqnders on 24/05/18.
//

#include "PrepareConfiguration.h"

#include <utils/Logger.h>
#include "ConfiguringState.h"

namespace machinestates {

PrepareConfiguration::PrepareConfiguration(machinecore::Machine &aContext) : MachineState(aContext) {
  utils::Logger::log(__PRETTY_FUNCTION__);
}

void PrepareConfiguration::entryAction() {

}

void PrepareConfiguration::doActivity() {
  MachineState::doActivity();
}

void PrepareConfiguration::exitAction() {

}

bool PrepareConfiguration::handleEvent(const machinestates::EventPtr &event) {
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

void PrepareConfiguration::onReconfigure(const EventPtr &event) {
  utils::Logger::log("-Handle event: kEventTypeReconfigure");

  auto nextConfig = context.getConfigurations().at(event->getArgumentAsType<uint16_t>());
  context.setCurrentConfiguration(nextConfig);

  auto state = std::make_shared<ConfiguringState>(context);
  context.setCurrentState(state);
}
} // machinestates