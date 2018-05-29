//
// Created by don on 28-5-18.
//

#include "Application.h"

void visualizercore::Application::scheduleEvent(const visualizercore::Event &anEvent) {
  //Check if time is not before the last event
  if(anEvent.getTime() >= events.back().getTime()) {
    events.push_back(anEvent);
  }
}
void visualizercore::Application::addMachine(const visualizercore::Machine &aMachine) {
  machines.push_back(aMachine);
}
