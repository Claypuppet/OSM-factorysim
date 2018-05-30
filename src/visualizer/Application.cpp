//
// Created by don on 28-5-18.
//

#include "Application.h"

namespace visualisercore {

void Application::scheduleEvent(const EventPtr &anEvent) {
  //Check if time is not before the last event
  if (anEvent->getTime() >= events.back()->getTime()) {
    events.push_back(anEvent);
  }
  else{
    throw std::runtime_error("Can't schedule event!");
  }
}
void Application::addMachine(const MachinePtr &aMachine) {
  machines.push_back(aMachine);
}

}
