add_library(source_lib_app_production SHARED
        configuration_reader/ConfigurationReader.cpp
        configuration_reader/ConfigurationReader.h
        configuration_reader/deserialize_strategies/JSONStrategy.cpp
        configuration_reader/deserialize_strategies/JSONStrategy.h
        configuration_reader/deserialize_strategies/YAMLStrategy.cpp
        configuration_reader/deserialize_strategies/YAMLStrategy.h
        ConnectionHandler.h
        ConnectionHandler.cpp
        Machine.cpp
        Machine.h
        Product.cpp
        Product.h
        Buffer.cpp
        Buffer.h
        Application.cpp
        Application.h
        SimulationConnectionHandler.cpp
        SimulationConnectionHandler.h
        SimulationController.cpp
        SimulationController.h
        SimulationMachine.cpp
        SimulationMachine.h
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
        states_application/BroadCastState.cpp
        states_application/BroadCastState.h
        states_application/WaitForConnectionsState.h
        states_application/WaitForConnectionsState.cpp
        states_application/ApplicationState.cpp
        states_application/ApplicationState.h
        states_application/InOperationState.cpp
        states_application/InOperationState.h)

# Link to libs
target_link_libraries(source_lib_app_production lib_yaml-cpp lib_models lib_network lib_patterns lib_utils)

add_executable(app_production_control
        Main.cpp)

target_link_libraries(app_production_control source_lib_app_production)


# For production control, move configuration dir to bin dir
add_custom_command(TARGET app_production_control PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/configs" $<TARGET_FILE_DIR:app_production_control>/configs)
