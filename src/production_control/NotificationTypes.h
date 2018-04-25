//
// Created by don on 24-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_NOTIFICATIONTYPES_H
#define PRODUCTION_LINE_CONTROL_NOTIFICATIONTYPES_H

enum ApplicationNotificationTypes
{
    ApplicationRegisterMachine = 0,
    ApplicationStartInit,
    ApplicationStartProcessing,
    ApplicationDoneProcessing,
    ApplicationMachineReady,
    ApplicationOK,
    ApplicationNOK
};

enum SimulationNotificationTypes
{
    SimulationregisterMachine = 100
};

#endif //PRODUCTION_LINE_CONTROL_NOTIFICATIONTYPES_H
