#ifndef PRODUCTION_LINE_CONTROL_CONTROLLERNOTIFICATIONEVENTIDS_H
#define PRODUCTION_LINE_CONTROL_CONTROLLERNOTIFICATIONEVENTIDS_H

namespace ControllerEvents {
enum NotifyEventType {
  kNotifyEventTypeSimulationConfigurationsReceived,
  kNotifyEventTypeTurnOffReceived,
  kNotifyEventTypeTurnOnReceived,
  kNotifyEventTypeServiceStarted,
  kNotifyEventTypeServiceError,
  kNotifyEventTypeServiceStopped
};
}

#endif //PRODUCTION_LINE_CONTROL_CONTROLLERNOTIFICATIONEVENTIDS_H