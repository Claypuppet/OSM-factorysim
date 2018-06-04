//
// Created by don on 29-5-18.
//

#include <sstream>
#include "StatusUpdateEvent.h"

namespace visualisercore {

StatusUpdateEvent::StatusUpdateEvent(uint64_t aTimeStamp,
                                     uint16_t aMachineId,
                                     models::Machine::MachineStatus aStatusUpdateType)
    : Event(aTimeStamp, aMachineId), statusUpdateType(aStatusUpdateType) {

}

StatusUpdateEvent::StatusUpdateEvent(const visualisercore::StatusUpdateEvent &other)
    : Event(other), statusUpdateType(other.statusUpdateType) {
}

StatusUpdateEvent &visualisercore::StatusUpdateEvent::operator=(const visualisercore::StatusUpdateEvent &rhs) {
  if (this != &rhs) {
    Event::operator=(rhs);
    statusUpdateType = rhs.statusUpdateType;
  }
  return *this;
}

models::Machine::MachineStatus StatusUpdateEvent::getStatusUpdateType() const {
  return statusUpdateType;
}
const std::string StatusUpdateEvent::toString() {
  std::stringstream output;

  output << "-StatusUpdateEvent: ";
  output << " timestamp:";
  output << getTime();
  output << " machineId:";
  output << getMachineId();
  output << " currentState:";
  output << statusUpdateType;

  return output.str();
}

}
