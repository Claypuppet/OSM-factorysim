add_library(source_lib_app_production SHARED
        ConnectionHandler.h
        ConnectionHandler.cpp
        Machine.cpp
        Machine.h
        Product.cpp
        Product.h
        Buffer.cpp
        Buffer.h
        InfiniteBuffer.cpp
        InfiniteBuffer.h
        ResultLogger.cpp
        ResultLogger.h
        Application.cpp
        Application.h
        SimulationConnectionHandler.cpp
        SimulationConnectionHandler.h
        SimulationController.cpp
        SimulationController.h
        SimulationMachine.cpp
        SimulationMachine.h
        SimulationMachineLocal.cpp
        SimulationMachineLocal.h
        SimulationApplication.cpp
        SimulationApplication.h
        Controller.cpp
        Controller.h
        NetworkMapper.cpp
        NetworkMapper.h
        states_controller/LoadConfigState.cpp
        states_controller/LoadConfigState.h
        states_controller/OperationState.cpp
        states_controller/OperationState.h
        states_controller/SimulationBroadcastState.h
        states_controller/SimulationBroadcastState.cpp
        states_controller/SimulationWaitForConnectionsState.cpp
        states_controller/SimulationWaitForConnectionsState.h
        states_controller/ControllerState.cpp
        states_controller/ControllerState.h
        states_controller/FinishedOperationState.cpp
        states_controller/FinishedOperationState.h
        states_application/BroadCastState.cpp
        states_application/BroadCastState.h
        states_application/WaitForConnectionsState.h
        states_application/WaitForConnectionsState.cpp
        states_application/ApplicationState.cpp
        states_application/ApplicationState.h
        states_application/InOperationState.cpp
        states_application/InOperationState.h
        states_application/ShutdownState.cpp
        states_application/ShutdownState.h
        states_application/in_operation/PrepareSchedulerState.cpp
        states_application/in_operation/PrepareSchedulerState.h
        states_application/in_operation/PrepareShutdownState.cpp
        states_application/in_operation/PrepareShutdownState.h
        states_application/in_operation/PreChangeState.cpp
        states_application/in_operation/PreChangeState.h
        states_application/in_operation/OperatingState.cpp
        states_application/in_operation/OperatingState.h)

# Link to libs
target_link_libraries(source_lib_app_production lib_yaml-cpp lib_models lib_network lib_patterns lib_utils lib_configuration_serializer ${Boost_SYSTEM_LIBRARY} ${Boost_FILESYSTEM_LIBRARY})

add_executable(app_production_control
        Main.cpp)

target_link_libraries(app_production_control source_lib_app_production source_lib_app_machine_control)


# For production control, move configuration dir to bin dir

add_custom_target(config_mover ALL
        DEPENDS move_config)

add_custom_command(OUTPUT move_config
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/configs/" ${CMAKE_CURRENT_BINARY_DIR}/configs)

add_dependencies(app_production_control config_mover)
