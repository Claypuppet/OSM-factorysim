//
// Created by don on 29-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_STATUSUPDATEEVENT_H
#define PRODUCTION_LINE_CONTROL_STATUSUPDATEEVENT_H

#include "Event.h"
#include "../Machine.h"

namespace visualisercore {

/**
 * A class with information about a machine status update
 */
class StatusUpdateEvent : public Event {
 public:
  StatusUpdateEvent() = delete;
  StatusUpdateEvent(uint64_t aTimeStamp, uint16_t aMachineId, models::Machine::MachineStatus aStatusUpdateType);
  StatusUpdateEvent(const StatusUpdateEvent &other);
  StatusUpdateEvent &operator=(const StatusUpdateEvent &rhs);

  models::Machine::MachineStatus getStatusUpdateType() const;
  const std::string toString() override;
 private:
  models::Machine::MachineStatus statusUpdateType;
};

}

#endif //PRODUCTION_LINE_CONTROL_STATUSUPDATEEVENT_H
