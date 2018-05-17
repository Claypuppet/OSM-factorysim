//
// Created by sven on 9-5-18.
//

#include <utils/Logger.h>
#include "ReceiveConfig.h"
#include "Inititalization/ConfigureState.h"

namespace productionstates {
void ReceiveConfig::entryAction() {
  utils::Logger::log(__PRETTY_FUNCTION__);
  context.registerMachine();
}

void ReceiveConfig::doActivity() {

}

void ReceiveConfig::exitAction() {

}

bool ReceiveConfig::handleEvent(const EventPtr &event) {
  switch (event->getId()) {
    case kEventTypeReceivedConfig: {
      onConfigReceived(event);
      break;
    }
    default:return false;
  }
}

void ReceiveConfig::onConfigReceived(const EventPtr &event) {
  if (context.setCurrentConfigId(event->getArgumentAsType<uint32_t>())) {
    context.setCurrentState(std::make_shared<ConfigureState>(context));
  }
}
}