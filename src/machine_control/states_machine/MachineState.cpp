#include "MachineState.h"
#include "../NotificationEventTypes.h"

namespace machinestates {

MachineState::MachineState(machinecore::Machine &aContext) : context(aContext){

}

void MachineState::doActivity() {
}

bool MachineState::handleEvent(const EventPtr &event){
  switch(event->getId()){
    case kEventTypeMachineBroke: {
      onMachineBroke();
      return true;
    }
    default: {
      return false;
    }
  }
}

void MachineState::onMachineBroke() {
  auto notification = patterns::notifyobserver::NotifyEvent(machinecore::kNotifyEventTypeMachineBroke);
  context.notifyObservers(notification);
}
} // machinestates