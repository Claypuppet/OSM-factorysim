//
// Created by sven on 9-5-18.
//

#include "ReceiveConfig.h"
#include "Inititalization/ConfigureState.h"

namespace productionstates {
void ReceiveConfig::entryAction() {

}

void ReceiveConfig::doActivity() {

}

void ReceiveConfig::exitAction() {

}

bool ReceiveConfig::handleEvent(const patterns::statemachine::EventPtr &e) {
  switch (e->getId()) {
    case kEventTypeReceivedConfig: {
      if(context.configAvailable(e->getArgumentAsType<uint32_t >())) {
        context.setCurrentState(std::make_shared<ConfigureState>(context));
      }
      break;
    }
    default:return false;
  }
}
}