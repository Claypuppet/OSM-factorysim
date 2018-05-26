#include "ApplicationState.h"

namespace applicationstates{

ApplicationState::ApplicationState(machinecore::Application &aContext) : context(aContext) {

}

bool ApplicationState::handleEvent(const EventPtr &event){
  return false;
}

} // applicationstates