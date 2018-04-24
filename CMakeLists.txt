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
        src/machine_control/NetworkComponent.h
        src/machine_control/states_simulation/SimulationState.cpp
        src/machine_control/states_simulation/SimulationState.h
        src/machine_control/states_simulation/InitializeSimulationState.cpp
        src/machine_control/states_simulation/InitializeSimulationState.h
        src/machine_control/states_simulation/OffState.cpp
        src/machine_control/states_simulation/OffState.h
        src/machine_control/states_simulation/OnState.cpp
        src/machine_control/states_simulation/OnState.h
        src/machine_control/states_simulation/ShutdownState.cpp
        src/machine_control/states_simulation/ShutdownState.h
        src/machine_control/states_simulation/Event.cpp
        src/machine_control/states_simulation/Event.h)

add_executable(app_production_control
        src/production_control/Main.cpp
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
        src/production_control/Controller.h)


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
        lib_logger
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)


### LINK LIBRARIES ###

# Libs
target_link_libraries(lib_silly_objects ${wxWidgets_LIBRARIES} ${Boost_DATE_TIME_LIBRARY})
target_link_libraries(lib_network lib_logger ${Boost_SYSTEM_LIBRARY})

# Production control & test
target_link_libraries(app_production_control lib_network lib_silly_objects lib_logger)
target_link_libraries(test_production_control ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} lib_silly_objects)

# Machine control & test
target_link_libraries(app_machine_control lib_network lib_patterns)
target_link_libraries(app_machine_control lib_network lib_silly_objects lib_logger)
target_link_libraries(test_machine_control ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} lib_silly_objects)

# Visualizer & test
target_link_libraries(app_visualizer ${wxWidgets_LIBRARIES} lib_silly_objects lib_logger)
target_link_libraries(test_visualizer ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${wxWidgets_LIBRARIES} lib_silly_objects)

