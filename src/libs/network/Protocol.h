//
// Created by klei on 4/23/18.
//

#ifndef PRODUCTION_LINE_CONTROL_PROTOCOL_H
#define PRODUCTION_LINE_CONTROL_PROTOCOL_H

namespace Network {
	namespace Protocol {

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

		enum DiscoverMessageType {
//			For UPD connection
//			250 - PC - MC - Broadcast connection point (ip address) for existing machines to connect
//			251 - MC - PC - Request PC location (PC will respond 101)

			kDiscoverMessageTypePCIP = 250,
			kDiscoverMessageTypeRequestPCIP
		};

	}
}

#endif //PRODUCTION_LINE_CONTROL_PROTOCOL_H
