//
// Created by don on 24-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_NOTIFICATIONTYPES_H
#define PRODUCTION_LINE_CONTROL_NOTIFICATIONTYPES_H

namespace NotifyEventIds {

	enum ApplicationNotificationTypes
	{
		eApplicationRegisterMachine = 0,
		eApplicationStartInit,
		eApplicationStartProcessing,
		eApplicationDoneProcessing,
		eApplicationMachineReady,
		eApplicationOK,
		eApplicationNOK
	};

	enum ControllerNotificationTypes
	{
		eControllerRegisterMachine = 100,
		eControllerMachineReady

	};

}

#endif //PRODUCTION_LINE_CONTROL_NOTIFICATIONTYPES_H
