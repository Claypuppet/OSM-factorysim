//
// Created by klei on 4/23/18.
//

#ifndef PRODUCTION_LINE_CONTROL_PROTOCOL_H
#define PRODUCTION_LINE_CONTROL_PROTOCOL_H

namespace Network {
	namespace Protocol {

		enum DiscoverMessageType {
//			For UPD connection
//			Find Machines	PC	Broadcast (MC)	250	(ip address?)	Broadcast connection point (ip address) for existing machines to connect
//			Find Production control	MC	Broadcast (PC)	251	-	Request PC location (PC will respond with 250)


			kDiscoverMessageTypePCIP = 250,
			kDiscoverMessageTypeRequestPCIP
		};

		enum SimMessageType {
//			101 - PC - MC - Machine configurations for the simulation
//			102 - PC - MC - Turn machine on
//			103 - PC - MC - Shutdown machine

			kSimMessageTypeConfig = 101,
			kSimMessageTypeTurnOn,
			kSimMessageTypeTurnOff

		};

		enum AppMessageType {
//			1 - MC - PC - Send id of machine

//			10 - PC - MC - Start process product
//			11 - PC - MC - Reconfigure

//			20 - MC - PC - Ready for command
//			21 - MC - PC - Started initializing
//			22 - MC - PC - Start reconfigure
//			23 - MC - PC - Started processing
//			24 - MC - PC - Done processing

//			50 - MC - PC - Response OK
//			51 - MC - PC - Response NOK

			kAppMessageTypeRegisterMachine = 1,
			kAppMessageTypeInitialConfigure,

			kAppMessageTypeStartProcess = 10,
			kAppMessageTypeReconfigure,

			kAppMessageTypeReady = 20,
			kAppMessageTypeStartedInitialize,
			kAppMessageTypeStartedReconfigure,
			kAppMessageTypeStartedProcessing,
			kAppMessageTypeDoneProcessing,

			kAppMessageTypeOK = 50,
			kAppMessageTypeNOK,
		};

	}
}

#endif //PRODUCTION_LINE_CONTROL_PROTOCOL_H
