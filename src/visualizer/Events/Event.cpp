//
// Created by don on 28-5-18.
//

#include "Event.h"

namespace visualisercore {

Event::Event(uint64_t aTimeStamp,
             uint16_t aMachineId)
:timeStamp(aTimeStamp),machineId(aMachineId){

}

Event::Event(const Event &anEvent)
    : timeStamp(anEvent.timeStamp), machineId(anEvent.machineId) {

}
Event &Event::operator=(const Event &anEvent) {
  if (this != &anEvent) {
    timeStamp = anEvent.timeStamp;
    machineId = anEvent.machineId;
  }
  return *this;
}
uint64_t Event::getTime() const {
  return timeStamp;
}
uint16_t Event::getMachineId() const {
  return machineId;
}

}