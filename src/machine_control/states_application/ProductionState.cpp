
#include "ProductionState.h"

namespace productionstates {
ProductionState::ProductionState(machinecore::Application &aContext)
	: context(aContext) {
}

bool ProductionState::handleEvent(const EventPtr &event) {
  switch (event->getId()) {
	default:
	  return false;
  }
}

}