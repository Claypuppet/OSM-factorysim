add_library(source_lib_app_production SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/ConfigurationReader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ConfigurationReader.h
        ${CMAKE_CURRENT_SOURCE_DIR}/AppConnectionHandler.h
        ${CMAKE_CURRENT_SOURCE_DIR}/AppConnectionHandler.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Machine.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Machine.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Product.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Product.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ResultLogger.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ResultLogger.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Buffer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Buffer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Application.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Application.h
        ${CMAKE_CURRENT_SOURCE_DIR}/SimulationConnectionHandler.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/SimulationConnectionHandler.h
        ${CMAKE_CURRENT_SOURCE_DIR}/SimulationController.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/SimulationController.h
        ${CMAKE_CURRENT_SOURCE_DIR}/SimulationMachine.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/SimulationMachine.h
        ${CMAKE_CURRENT_SOURCE_DIR}/SimulationApplication.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/SimulationApplication.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Controller.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Controller.h
        ${CMAKE_CURRENT_SOURCE_DIR}/NetworkMapper.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/NetworkMapper.h
        ${CMAKE_CURRENT_SOURCE_DIR}/states_controller/LoadConfigState.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/states_controller/LoadConfigState.h
        ${CMAKE_CURRENT_SOURCE_DIR}/states_controller/OperationState.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/states_controller/OperationState.h
        ${CMAKE_CURRENT_SOURCE_DIR}/states_controller/SimulationBroadcastState.h
        ${CMAKE_CURRENT_SOURCE_DIR}/states_controller/SimulationBroadcastState.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/states_controller/SimulationWaitForConnectionsState.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/states_controller/SimulationWaitForConnectionsState.h
        ${CMAKE_CURRENT_SOURCE_DIR}/states_controller/ControllerState.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/states_controller/ControllerState.h
        ${CMAKE_CURRENT_SOURCE_DIR}/states_application/BroadCastState.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/states_application/BroadCastState.h
        ${CMAKE_CURRENT_SOURCE_DIR}/states_application/WaitForConnectionsState.h
        ${CMAKE_CURRENT_SOURCE_DIR}/states_application/WaitForConnectionsState.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/states_application/ApplicationState.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/states_application/ApplicationState.h
        ${CMAKE_CURRENT_SOURCE_DIR}/states_application/InOperationState.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/states_application/InOperationState.h)

# Link to libs
target_link_libraries(source_lib_app_production lib_yaml-cpp lib_models lib_network lib_patterns lib_utils)
