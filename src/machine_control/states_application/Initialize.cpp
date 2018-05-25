//
// Created by sven on 9-5-18.
//

#include <utils/Logger.h>
#include "Initialize.h"
#include "ConfigureState.h"

namespace applicationstates {

Initialize::Initialize(machinecore::Application &aContext) : ApplicationState(aContext) {

}

void Initialize::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);
  context.registerMachine();
}

void Initialize::doActivity() {

}

void Initialize::exitAction() {

}

bool Initialize::handleEvent(const EventPtr &event) {
  switch (event->getId()) {
    case kEventTypeReceivedConfig: {
      onReceivedConfig(event);
      return true;
    }

    default: {
      return false;
    }
  }
}

void Initialize::onReceivedConfig(const EventPtr &event) {
  utils::Logger::log("-Handle event: kEventTypeReceivedConfig");

  context.setConfigToSet(event->getArgumentAsType<uint16_t>());

  auto state = std::make_shared<ConfigureState>(context);
  context.setCurrentState(state);
}
} // applicationstates