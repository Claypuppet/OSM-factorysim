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

namespace machinecore {

/**
 * Event types for notifications in application
 */
enum NotifyEventType {
  kNotifyEventTypeServiceStarted,
  kNotifyEventTypeServiceError,
  kNotifyEventTypeStartProcess,
  kNotifyEventTypeProductTakenFromBuffer,
  kNotifyEventTypeMachineConfigured,
  kNotifyEventTypeMachineFailedToConfigure,
  kNotifyEventTypeConfigure,
  kNotifyEventTypeProductAddedToBuffer,
  kNotifyEventTypeMachineFinishedProcess,
  kNotifyEventTypeMachineBroke
};
}

#endif //PRODUCTION_LINE_CONTROL_CONTROLLERNOTIFICATIONEVENTIDS_H