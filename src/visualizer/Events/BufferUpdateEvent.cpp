//
// Created by don on 29-5-18.
//

#include <sstream>
#include "BufferUpdateEvent.h"

namespace visualisercore {

BufferUpdateEvent::BufferUpdateEvent(uint64_t aTimeStamp,
                                     uint16_t aMachineId,
                                     uint16_t aProductId,
                                     uint32_t aBufferAmmount)
    : Event(aTimeStamp, aMachineId), productId(aProductId), bufferAmount(aBufferAmmount) {

}

BufferUpdateEvent::BufferUpdateEvent(const BufferUpdateEvent &other)
    : Event(other), productId(other.productId), bufferAmount(other.bufferAmount) {

}

BufferUpdateEvent &BufferUpdateEvent::operator=(const BufferUpdateEvent &rhs) {
  if (this != &rhs) {
    Event::operator=(rhs);
    productId = rhs.productId;
    bufferAmount = rhs.bufferAmount;
  }
  return *this;
}

uint16_t BufferUpdateEvent::getProductId() const {
  return productId;
}

uint32_t BufferUpdateEvent::getBufferAmount() const {
  return bufferAmount;
}
const std::string BufferUpdateEvent::toString() {
  std::stringstream output;

  output << "-ConfigUpdateEvent: ";
  output << " timestamp:";
  output << getTime();
  output << " machineId:";
  output << getMachineId();
  output << " productId:";
  output << productId;
  output << " bufferAmount:";
  output << bufferAmount;

  return output.str();
}

}