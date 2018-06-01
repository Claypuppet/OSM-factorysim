//
// Created by hqnders on 24/05/18.
//

#include "PrepareConfiguration.h"

#include <utils/Logger.h>
#include "ConfiguringState.h"

namespace machinestates {

PrepareConfiguration::PrepareConfiguration(machinecore::Machine &aContext) : MachineState(aContext) {
}

void PrepareConfiguration::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);
}

void PrepareConfiguration::doActivity() {
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
//  utils::Logger::log("-Handle event: kEventTypeReconfigure");

  auto nextConfig = context.getConfigurationById(event->getArgumentAsType<uint16_t>());
  context.setCurrentConfiguration(nextConfig);

  std::stringstream ss;
  ss << "-Reconfiguring for new product: " << nextConfig;
  utils::Logger::log(ss.str());

  auto state = std::make_shared<ConfiguringState>(context);
  context.setCurrentState(state);
}
} // machinestates