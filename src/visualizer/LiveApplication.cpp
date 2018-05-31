//
// Created by don on 28-5-18.
//

#include "LiveApplication.h"

namespace live {

void LiveApplication::scheduleProductionEvent(const visualisercore::EventPtr &anEvent) {
  //Check if time is not before the last event
  if (anEvent->getTime() >= productionEvents.back()->getTime()) {
    productionEvents.push_back(anEvent);
  } else {
    throw std::runtime_error("Can't schedule event!");
  }
}

}