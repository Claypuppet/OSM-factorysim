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
        src/machine_control/Main.cpp)

add_executable(app_production_control
        src/production_control/Main.cpp
        src/production_control/CommNet.cpp src/production_control/Machine.cpp src/production_control/Machine.h src/production_control/Application.cpp src/production_control/Application.h)

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
        "src/libs/patterns/**.h"
        "src/libs/patterns/**.cpp")

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


install(TARGETS
        lib_silly_objects
        lib_network
        lib_patterns
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)


### LINK LIBRARIES ###

# Libs
target_link_libraries(lib_silly_objects ${wxWidgets_LIBRARIES} ${Boost_DATE_TIME_LIBRARY})
target_link_libraries(lib_network ${Boost_SYSTEM_LIBRARY})


# Production control & test
target_link_libraries(app_production_control lib_network lib_silly_objects)
target_link_libraries(test_production_control ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} lib_silly_objects)

# Machine control & test
target_link_libraries(app_machine_control lib_network)
target_link_libraries(test_machine_control ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} lib_silly_objects)

# Visualizer & test
target_link_libraries(app_visualizer ${wxWidgets_LIBRARIES} lib_silly_objects)
target_link_libraries(test_visualizer ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${wxWidgets_LIBRARIES} lib_silly_objects)

