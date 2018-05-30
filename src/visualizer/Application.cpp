//
// Created by don on 28-5-18.
//

#include "Application.h"

namespace visualisercore {

void Application::scheduleEvent(const Event &anEvent) {
  //Check if time is not before the last event
  if (anEvent.getTime() >= events.back().getTime()) {
    events.push_back(anEvent);
  }
}
void Application::addMachine(const Machine &aMachine) {
  machines.push_back(aMachine);
}

}
