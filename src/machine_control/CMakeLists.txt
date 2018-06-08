
add_library(source_lib_app_machine_control SHARED
        NotificationEventTypes.h
        SimulationNetworkComponent.cpp
        SimulationNetworkComponent.h
        Controller.cpp
        Controller.h
        Application.cpp
        Application.h
        SimulationController.cpp
        SimulationController.h
        SimulationApplication.cpp
        SimulationApplication.h
        NetworkComponent.cpp
        NetworkComponent.h
        states_application/ApplicationState.h
        states_application/ApplicationState.cpp
        states_application/Initialize.cpp
        states_application/Initialize.h
        states_application/ConnectState.cpp
        states_application/ConnectState.h
        states_application/BrokenState.cpp
        states_application/BrokenState.h
        states_application/ConfigureState.cpp
        states_application/ConfigureState.h
        states_application/IdleState.cpp
        states_application/IdleState.h
        states_application/InOperationState.h
        states_application/InOperationState.cpp
        states_machine/Configure/ConfiguringState.cpp
        states_machine/Configure/ConfiguringState.h
        states_machine/Configure/SelfTestState.cpp
        states_machine/Configure/SelfTestState.h
        states_machine/Configure/PrepareConfiguration.cpp
        states_machine/Configure/PrepareConfiguration.h
        states_machine/InOperation/TakeProductState.cpp
        states_machine/InOperation/TakeProductState.h
        states_machine/InOperation/ProcessProductState.cpp
        states_machine/InOperation/ProcessProductState.h
        states_machine/InOperation/TakeOutProductState.cpp
        states_machine/InOperation/TakeOutProductState.h
        states_machine/MachineState.h
        states_machine/MachineState.cpp
        states_simulation_controller/SimulationState.cpp
        states_simulation_controller/SimulationState.h
        states_simulation_controller/InitializeSimulationState.cpp
        states_simulation_controller/InitializeSimulationState.h
        states_simulation_controller/OffState.cpp
        states_simulation_controller/OffState.h
        states_simulation_controller/OnState.cpp
        states_simulation_controller/OnState.h
        states_simulation_controller/FindProductControlState.cpp
        states_simulation_controller/FindProductControlState.h
        states_simulation_controller/ConnectSimulationState.cpp
        states_simulation_controller/ConnectSimulationState.h
        states_simulation_controller/WaitForProductControlState.cpp
        states_simulation_controller/WaitForProductControlState.h
        Machine.h
        SimulationMachine.cpp
        SimulationMachine.h
        )

target_link_libraries(source_lib_app_machine_control lib_network lib_patterns lib_models)

add_executable(app_machine_control
        Main.cpp)

target_link_libraries(app_machine_control source_lib_app_machine_control)