//
// Created by don on 28-5-18.
//

#include "Event.h"

namespace visualizercore {

Event::Event(uint64_t aTimeStamp,
                             uint16_t aMachineId,
                             eVisualizerEventTypes anEventType) {

}

eVisualizerEventTypes Event::getEventType() const {
  return eventType;
}

Event::Event(const Event &anEvent)
    : timeStamp(anEvent.timeStamp), machineId(anEvent.machineId), eventType(anEvent.eventType) {

}
Event &Event::operator=(const Event &anEvent) {
  if (this != &anEvent) {
    timeStamp = anEvent.timeStamp;
    machineId = anEvent.machineId;
    eventType = anEvent.eventType;
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