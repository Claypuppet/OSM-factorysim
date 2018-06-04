//
// Created by don on 28-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_EVENT_H
#define PRODUCTION_LINE_CONTROL_EVENT_H

#include <cstdint>
#include <string>
#include <memory>

namespace visualisercore {

/**
 * Events that show status updates in machines
 */
class Event {
 public:
  Event() = delete;
  Event(uint64_t aTimeStamp, uint16_t aMachineId);
  Event(const Event& anEvent);
  Event& operator=(const Event& anEvent);
  uint64_t getTime() const;
  uint16_t getMachineId() const;

  /**
   * A function that generates a string with information about the event
   * @return : String with information about the event
   */
  virtual const std::string toString() = 0;
 private:
  uint64_t timeStamp;
  uint16_t machineId;
};

typedef std::shared_ptr<Event> EventPtr;

}

#endif //PRODUCTION_LINE_CONTROL_EVENT_H
