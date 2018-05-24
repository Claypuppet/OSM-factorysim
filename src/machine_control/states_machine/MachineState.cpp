#include "MachineState.h"

namespace machinestates {

MachineState::MachineState(machinecore::Machine &aContext) : context(aContext){

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

} // machinestates