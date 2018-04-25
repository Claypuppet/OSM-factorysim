cmake_minimum_required(VERSION 3.3)
project(production_line_control)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_CXX_STANDARD 11)


include_directories(src/libs)

find_package(wxWidgets REQUIRED net gl core base)
include(${wxWidgets_USE_FILE})

find_package(Boost REQUIRED COMPONENTS system unit_test_framework)
link_directories(${Boost_LIBRARY_DIR} )


### SET APPLICATION EXECUTABLES ###

# Add

add_executable(app_machine_control
        src/machine_control/Main.cpp
        src/machine_control/SimulationNetworkComponent.cpp
        src/machine_control/SimulationNetworkComponent.h
        src/machine_control/Controller.cpp
        src/machine_control/Controller.h
        src/machine_control/Application.cpp
        src/machine_control/Application.h
        src/machine_control/SimulationController.cpp
        src/machine_control/SimulationController.h
        src/machine_control/SimulationApplication.cpp
        src/machine_control/SimulationApplication.h
        src/machine_control/NetworkComponent.cpp
        src/machine_control/states_production/Broken/BrokenState.cpp src/machine_control/states_production/Broken/BrokenState.h src/machine_control/states_production/ProductionState.cpp src/machine_control/states_production/ProductionState.h src/machine_control/states_production/Broken/RepairingState.cpp src/machine_control/states_production/Broken/RepairingState.h src/machine_control/states_production/Inititalization/ConfigureState.cpp src/machine_control/states_production/Inititalization/ConfigureState.h src/machine_control/states_production/Inititalization/SelfTestState.cpp src/machine_control/states_production/Inititalization/SelfTestState.h src/machine_control/states_production/ConnectState.cpp src/machine_control/states_production/ConnectState.h src/machine_control/states_production/InOperation/IdleState.cpp src/machine_control/states_production/InOperation/IdleState.h src/machine_control/states_production/InOperation/ProcessProduct/TakeProductState.cpp src/machine_control/states_production/InOperation/ProcessProduct/TakeProductState.h src/machine_control/states_production/InOperation/ProcessProduct/ProcessProductState.cpp src/machine_control/states_production/InOperation/ProcessProduct/ProcessProductState.h src/machine_control/states_production/InOperation/ProcessProduct/TakeOutProductState.cpp src/machine_control/states_production/InOperation/ProcessProduct/TakeOutProductState.h
        src/machine_control/NetworkComponent.h
        src/machine_control/states_simulation/SimulationState.cpp
        src/machine_control/states_simulation/SimulationState.h
        src/machine_control/states_simulation/InitializeSimulationState.cpp
        src/machine_control/states_simulation/InitializeSimulationState.h
        src/machine_control/states_simulation/OffState.cpp
        src/machine_control/states_simulation/OffState.h
        src/machine_control/states_simulation/OnState.cpp
        src/machine_control/states_simulation/OnState.h
        src/machine_control/states_simulation/FindProductControlState.cpp
        src/machine_control/states_simulation/FindProductControlState.h
        src/machine_control/states_simulation/ConnectSimulationState.cpp
        src/machine_control/states_simulation/ConnectSimulationState.h
        src/machine_control/config.h )

add_executable(app_production_control
        src/production_control/Main.cpp
        src/production_control/ConfigurationReader.cpp
        src/production_control/ConfigurationReader.h
        src/production_control/AppConnectionHandler.h
        src/production_control/AppConnectionHandler.cpp
        src/production_control/Machine.cpp
        src/production_control/Machine.h
        src/production_control/Application.cpp
        src/production_control/Application.h
        src/production_control/TestConnectionHandler.cpp
        src/production_control/TestConnectionHandler.h
        src/production_control/SimulationController.cpp
        src/production_control/SimulationController.h
        src/production_control/Controller.cpp
        src/production_control/Controller.h
        src/production_control/SimulationConnectionHandler.cpp
        src/production_control/SimulationConnectionHandler.h
        src/production_control/NotificationTypes.h)


add_executable(app_visualizer
        src/visualizer/Main.cpp)


### SET APPLICATION TEST EXECUTABLES ###

add_executable(test_machine_control
        tests/machine_control/Main.cpp
        tests/machine_control/Object_test.cpp)

add_executable(test_production_control
        tests/production_control/Main.cpp
        tests/production_control/Object_test.cpp)

add_executable(test_visualizer
        tests/visualizer/Main.cpp
        tests/visualizer/Object_test.cpp)

### SET APPLICATION LIBRARIES ###

# Lib Network
file(GLOB lib_network_SRC
        "src/libs/network/**.h"
        "src/libs/network/**.cpp")

add_library(lib_network SHARED
        ${lib_network_SRC})

# Lib Models
file(GLOB lib_models_SRC
        "src/libs/models/**.h"
        "src/libs/models/**.cpp")

add_library(lib_models SHARED
        ${lib_models_SRC})

# Lib Patterns
file(GLOB lib_patterns_SRC
        "src/libs/patterns/statemachine/**.h"
        "src/libs/patterns/statemachine/**.cpp"
        "src/libs/patterns/singleton/**.h"
        "src/libs/patterns/singleton/**.cpp"
        "src/libs/patterns/notifyobserver/**.h"
        "src/libs/patterns/notifyobserver/**.cpp")

add_library(lib_patterns SHARED
        ${lib_patterns_SRC})

# Lib yaml-cpp
file(GLOB lib_yaml_SRC
        "src/libs/yaml-cpp/include/yaml-cpp/**.h"
        "src/libs/yaml-cpp/src/**.cpp")

add_library(lib_yaml-cpp SHARED
        ${lib_yaml_SRC})

# Lib Cereal
file(GLOB lib_cereal_SRC
        "src/libs/cereal/**.hpp")

add_library(lib_cereal INTERFACE)
target_sources(lib_cereal INTERFACE ${lib_cereal_SRC})


# Lib Silly objects
file(GLOB lib_silly_objects_SRC
        "src/libs/silly_objects/**.hpp"
        "src/libs/silly_objects/**.cpp")

add_library(lib_silly_objects SHARED
        ${lib_silly_objects_SRC})

# Lib logger
file(GLOB lib_logger_SRC
        "src/libs/Logger/**.h"
        "src/libs/Logger/**.cpp")

add_library(lib_logger SHARED
        ${lib_logger_SRC})


install(TARGETS
        lib_silly_objects
        lib_network
        lib_patterns
        lib_yaml-cpp
        lib_models
        lib_logger
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)


### LINK LIBRARIES ###

# Libs
target_link_libraries(lib_silly_objects ${wxWidgets_LIBRARIES} ${Boost_DATE_TIME_LIBRARY})
target_link_libraries(lib_network lib_logger ${Boost_SYSTEM_LIBRARY})
target_link_libraries(lib_patterns ${Boost_SYSTEM_LIBRARY})

# Production control & test
target_link_libraries(app_production_control lib_yaml-cpp lib_models lib_network lib_logger lib_patterns)
target_link_libraries(test_production_control ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} lib_silly_objects)

# Machine control & test
target_link_libraries(app_machine_control lib_network lib_patterns)
target_link_libraries(app_machine_control lib_network lib_silly_objects lib_logger)
target_link_libraries(test_machine_control ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} lib_silly_objects)

# Visualizer & test
target_link_libraries(app_visualizer ${wxWidgets_LIBRARIES} lib_silly_objects lib_logger)
target_link_libraries(test_visualizer ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${wxWidgets_LIBRARIES} lib_silly_objects)

