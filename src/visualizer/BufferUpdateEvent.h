//
// Created by don on 29-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_BUFFERUPDATEEVENT_H
#define PRODUCTION_LINE_CONTROL_BUFFERUPDATEEVENT_H

#include "Event.h"

namespace visualisercore {

class BufferUpdateEvent : public Event {
 public:
  BufferUpdateEvent() = delete;
  BufferUpdateEvent(uint64_t aTimeStamp, uint16_t aMachineId, uint16_t aProductId, uint32_t aBufferAmmount);
  BufferUpdateEvent(const BufferUpdateEvent &other);
  BufferUpdateEvent &operator=(const BufferUpdateEvent &rhs);

  uint16_t getProductId() const;
  const std::string toString() override;
  uint32_t getBufferAmount() const;
 private:
  uint16_t productId;
  uint32_t bufferAmount;
};

}
#endif //PRODUCTION_LINE_CONTROL_BUFFERUPDATEEVENT_H
