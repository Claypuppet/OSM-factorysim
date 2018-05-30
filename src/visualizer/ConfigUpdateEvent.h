//
// Created by don on 29-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_CONFIGUPDATEEVENT_H
#define PRODUCTION_LINE_CONTROL_CONFIGUPDATEEVENT_H

#include <cstdint>
#include "Event.h"

namespace visualisercore {

class ConfigUpdateEvent : public Event{
 public:
  ConfigUpdateEvent() = delete;
  ConfigUpdateEvent(uint64_t aTimeStamp, uint16_t aMachineId, uint16_t aConfigId);
  ConfigUpdateEvent(const ConfigUpdateEvent &other);
  ConfigUpdateEvent &operator=(const ConfigUpdateEvent &rhs);

  uint16_t getConfigId() const;
  const std::string toString() override;
 private:
  uint16_t configId;
};

}

#endif //PRODUCTION_LINE_CONTROL_CONFIGUPDATEEVENT_H
