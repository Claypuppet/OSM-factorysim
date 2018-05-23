
add_library(source_lib_app_machine_control SHARED
        config.h
        ControllerNotificationEventIds.h
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
        states_application/Broken/BrokenState.cpp
        states_application/Broken/BrokenState.h
        states_application/ProductionState.cpp
        states_application/ProductionState.h
        states_application/ReceiveConfig.cpp
        states_application/ReceiveConfig.h
        states_application/Broken/RepairingState.cpp
        states_application/Broken/RepairingState.h
        states_application/Inititalization/ConfigureState.cpp
        states_application/Inititalization/ConfigureState.h
        states_application/Inititalization/SelfTestState.cpp
        states_application/Inititalization/SelfTestState.h
        states_application/ConnectState.cpp
        states_application/ConnectState.h
        states_application/InOperation/IdleState.cpp
        states_application/InOperation/IdleState.h
        states_application/InOperation/ProcessProduct/TakeProductState.cpp
        states_application/InOperation/ProcessProduct/TakeProductState.h
        states_application/InOperation/ProcessProduct/ProcessProductState.cpp
        states_application/InOperation/ProcessProduct/ProcessProductState.h
        states_application/InOperation/ProcessProduct/TakeOutProductState.cpp
        states_application/InOperation/ProcessProduct/TakeOutProductState.h
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
        states_application/InOperation/InOperationState.cpp
        states_application/InOperation/InOperationState.h
        states_simulation_controller/WaitForProductControlState.cpp
        states_simulation_controller/WaitForProductControlState.h
        Machine.cpp
        Machine.h
        SimulationMachine.cpp
        SimulationMachine.h)

target_link_libraries(source_lib_app_machine_control lib_network lib_patterns lib_models)

add_executable(app_machine_control
        Main.cpp)

target_link_libraries(app_machine_control source_lib_app_machine_control)