#ifndef PRODUCTION_LINE_CONTROL_CONTROLLERNOTIFICATIONEVENTIDS_H
#define PRODUCTION_LINE_CONTROL_CONTROLLERNOTIFICATIONEVENTIDS_H

namespace ControllerEvents {
    enum NotifyEventType {
        kNotifyEventTypeMachineInfoReceived,
        kNotifyEventTypeTurnOffReceived,
        kNotifyEventTypeTurnOnReceived
    };
}

#endif //PRODUCTION_LINE_CONTROL_CONTROLLERNOTIFICATIONEVENTIDS_H