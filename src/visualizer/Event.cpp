//
// Created by don on 28-5-18.
//

#include "Event.h"

visualizercore::Event::Event(uint64_t aTimeStamp,
                             uint16_t aMachineId,
                             visualizercore::eVisualizerEventTypes anEventType) {

}

visualizercore::eVisualizerEventTypes visualizercore::Event::getEventType() const {
  return eventType;
}
visualizercore::Event::Event(const visualizercore::Event &anEvent)
    : timeStamp(anEvent.timeStamp), machineId(anEvent.machineId), eventType(anEvent.eventType) {

}
visualizercore::Event &visualizercore::Event::operator=(const visualizercore::Event &anEvent) {
  if (this != &anEvent) {
    timeStamp = anEvent.timeStamp;
    machineId = anEvent.machineId;
    eventType = anEvent.eventType;
  }
  return *this;
}
uint64_t visualizercore::Event::getTime() const {
  return timeStamp;
}
uint16_t visualizercore::Event::getMachineId() const {
  return machineId;
}
