#include "MachineState.h"

#include "../Application.h"

namespace machinestates {

MachineState::MachineState(machinecore::Machine &aContext) : context(aContext){

}

void MachineState::doActivity() {
 //TODO: Check machine breaking
}

bool MachineState::handleEvent(const EventPtr &event){
  switch(event->getId()){
    case kEventTypeMachineBroke: {
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