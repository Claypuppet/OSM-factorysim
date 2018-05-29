//
// Created by don on 28-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_EVENT_H
#define PRODUCTION_LINE_CONTROL_EVENT_H

#include <cstdint>
namespace visualisercore {

/**
 * Enum for event types
 */
enum eVisualizerEventTypes {

};

/**
 * Events that show status updates in machines
 */
class Event {
 public:
  Event() = delete;
  Event(uint64_t aTimeStamp, uint16_t aMachineId, eVisualizerEventTypes anEventType);
  Event(const Event& anEvent);
  Event& operator=(const Event& anEvent);
  uint64_t getTime() const;
  uint16_t getMachineId() const;
  eVisualizerEventTypes getEventType() const;
 private:
  uint64_t timeStamp;
  uint16_t machineId;
  eVisualizerEventTypes eventType;
};

}

#endif //PRODUCTION_LINE_CONTROL_EVENT_H
