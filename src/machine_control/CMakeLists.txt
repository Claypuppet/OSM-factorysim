
add_library(source_lib_app_machine_control SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/config.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ControllerNotificationEventIds.h
        ${CMAKE_CURRENT_SOURCE_DIR}/SimulationNetworkComponent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/SimulationNetworkComponent.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Controller.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Controller.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Application.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Application.h
        ${CMAKE_CURRENT_SOURCE_DIR}/SimulationController.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/SimulationController.h
        ${CMAKE_CURRENT_SOURCE_DIR}/SimulationApplication.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/SimulationApplication.h
        ${CMAKE_CURRENT_SOURCE_DIR}/NetworkComponent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/NetworkComponent.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Machine.h
        ${CMAKE_CURRENT_SOURCE_DIR}/SimulationMachine.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/SimulationMachine.h

        ${CMAKE_CURRENT_SOURCE_DIR}/states_application/ApplicationState.h
        ${CMAKE_CURRENT_SOURCE_DIR}/states_application/ApplicationState.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/states_application/Initialize.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/states_application/Initialize.h
        ${CMAKE_CURRENT_SOURCE_DIR}/states_application/ConnectState.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/states_application/ConnectState.h

        states_application/BrokenState.cpp
        states_application/BrokenState.h
        states_application/ConfigureState.cpp
        states_application/ConfigureState.h
        states_application/IdleState.cpp
        states_application/IdleState.h
        states_application/InOperationState.cpp
        states_application/InOperationState.h
        ${CMAKE_CURRENT_SOURCE_DIR}/states_machine/MachineState.h
        ${CMAKE_CURRENT_SOURCE_DIR}/states_machine/MachineState.cpp
        states_machine/Configure/ConfiguringState.cpp
        states_machine/Configure/ConfiguringState.h
        states_machine/Configure/SelfTestState.cpp
        states_machine/Configure/SelfTestState.h
        states_machine/Configure/ReadyingConfigState.cpp
        states_machine/Configure/ReadyingConfigState.h

        states_machine/InOperation/TakeProductState.cpp
        states_machine/InOperation/TakeProductState.h
        states_machine/InOperation/ProcessProductState.cpp
        states_machine/InOperation/ProcessProductState.h
        states_machine/InOperation/TakeOutProductState.cpp
        states_machine/InOperation/TakeOutProductState.h

        ${CMAKE_CURRENT_SOURCE_DIR}/states_simulation_controller/SimulationState.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/states_simulation_controller/SimulationState.h
        ${CMAKE_CURRENT_SOURCE_DIR}/states_simulation_controller/InitializeSimulationState.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/states_simulation_controller/InitializeSimulationState.h
        ${CMAKE_CURRENT_SOURCE_DIR}/states_simulation_controller/OffState.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/states_simulation_controller/OffState.h
        ${CMAKE_CURRENT_SOURCE_DIR}/states_simulation_controller/OnState.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/states_simulation_controller/OnState.h
        ${CMAKE_CURRENT_SOURCE_DIR}/states_simulation_controller/FindProductControlState.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/states_simulation_controller/FindProductControlState.h
        ${CMAKE_CURRENT_SOURCE_DIR}/states_simulation_controller/ConnectSimulationState.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/states_simulation_controller/ConnectSimulationState.h
        ${CMAKE_CURRENT_SOURCE_DIR}/states_simulation_controller/WaitForProductControlState.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/states_simulation_controller/WaitForProductControlState.h)

target_link_libraries(source_lib_app_machine_control lib_network lib_patterns lib_models)
