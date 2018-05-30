//
// Created by don on 29-5-18.
//

#include <sstream>
#include "ConfigUpdateEvent.h"

namespace visualisercore {

ConfigUpdateEvent::ConfigUpdateEvent(uint64_t aTimeStamp, uint16_t aMachineId, uint16_t aConfigId)
    : Event(aTimeStamp,
            aMachineId),
      configId(aConfigId) {

}

ConfigUpdateEvent::ConfigUpdateEvent(const ConfigUpdateEvent &other)
    : Event(other), configId(other.configId) {

}

ConfigUpdateEvent &ConfigUpdateEvent::operator=(const ConfigUpdateEvent &rhs) {
  if (this != &rhs) {
    Event::operator=(rhs);
    configId = rhs.configId;
  }
  return *this;
}

uint16_t ConfigUpdateEvent::getConfigId() const{
  return configId;
}
const std::string ConfigUpdateEvent::toString() {
  std::stringstream output;

  output << "-ConfigUpdateEvent: ";
  output << " timestamp:";
  output << getTime();
  output << " machineId:";
  output << getMachineId();
  output << " configId:";
  output << configId;

  return output.str();
}

}