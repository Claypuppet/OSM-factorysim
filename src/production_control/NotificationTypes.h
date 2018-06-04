//
// Created by don on 24-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_NOTIFICATIONTYPES_H
#define PRODUCTION_LINE_CONTROL_NOTIFICATIONTYPES_H

namespace NotifyEventIds {

enum ApplicationNotificationTypes {
  eApplicationRegisterMachine = 0,
  eApplicationOK,
  eApplicationNOK
};

enum SimulationNotificationTypes {
  eSimRegisterMachine = 150,
  eSimMachineReady
};

}

#endif //PRODUCTION_LINE_CONTROL_NOTIFICATIONTYPES_H
