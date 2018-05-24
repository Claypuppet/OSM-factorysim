#ifndef PRODUCTION_LINE_CONTROL_STATE_INCLUSIONS_H
#define PRODUCTION_LINE_CONTROL_STATE_INCLUSIONS_H

#include "../../src/machine_control/states_application/ConfigureState.h"
#include "../../src/machine_control/states_application/ApplicationState.h"
#include "../../src/machine_control/states_application/BrokenState.h"
#include "../../src/machine_control/states_application/Initialize.h"
#include "../../src/machine_control/states_application/IdleState.h"
#include "../../src/machine_control/states_application/InOperationState.h"
#include "../../src/machine_control/states_application/ConnectState.h"

#include "../../src/machine_control/states_machine/Configure/ReadyingConfigState.h"
#include "../../src/machine_control/states_machine/Configure/ConfiguringState.h"
#include "../../src/machine_control/states_machine/Configure/SelfTestState.h"

#include "../../src/machine_control/states_machine/InOperation/TakeProductState.h"
#include "../../src/machine_control/states_machine/InOperation/ProcessProductState.h"
#include "../../src/machine_control/states_machine/InOperation/TakeOutProductState.h"

#include "../../src/machine_control/states_simulation_controller/WaitForProductControlState.h"
#include "../../src/machine_control/states_simulation_controller/InitializeSimulationState.h"
#include "../../src/machine_control/states_simulation_controller/ConnectSimulationState.h"
#include "../../src/machine_control/states_simulation_controller/FindProductControlState.h"
#include "../../src/machine_control/states_simulation_controller/OffState.h"
#include "../../src/machine_control/states_simulation_controller/OnState.h"

#endif //PRODUCTION_LINE_CONTROL_STATE_INCLUSIONS_H
