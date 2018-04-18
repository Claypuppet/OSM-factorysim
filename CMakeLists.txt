cmake_minimum_required(VERSION 3.3)
project(production_line_control)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")


include_directories(src/lib_silly_objects)

find_package(wxWidgets REQUIRED net gl core base)
include(${wxWidgets_USE_FILE})

find_package(Boost REQUIRED COMPONENTS system filesystem unit_test_framework)
link_directories(${Boost_LIBRARY_DIR} )


### SET APPLICATION EXECUTABLES ###

# Add

add_executable(app_machine_control
        src/machine_control/Main.cpp)

add_executable(app_production_control
        src/production_control/Main.cpp)

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
        "src/lib_network/**.h"
        "src/lib_network/**.cpp")

add_library(lib_network STATIC
        ${lib_network_SRC})

# Lib Cereal
file(GLOB lib_cereal_SRC
        "src/lib_cereal/**.hpp")

add_library(lib_cereal INTERFACE)
target_sources(lib_cereal INTERFACE ${lib_cereal_SRC})


# Lib Silly objects
file(GLOB lib_silly_objects_SRC
        "src/lib_silly_objects/**.hpp"
        "src/lib_silly_objects/**.cpp")

add_library(lib_silly_objects STATIC
        ${lib_silly_objects_SRC})


install(TARGETS
        lib_silly_objects
        lib_network
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)


### LINK LIBRARIES ###

# TODO: remove wxwidget library from lib after project startup, (and change boost to include asio)
target_link_libraries(lib_silly_objects ${wxWidgets_LIBRARIES} ${Boost_DATE_TIME_LIBRARY})


# Production control & test
target_link_libraries(app_production_control lib_silly_objects)
target_link_libraries(test_production_control ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} lib_silly_objects)

# Machine control & test
target_link_libraries(app_machine_control lib_silly_objects)
target_link_libraries(test_machine_control ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} lib_silly_objects)

# Visualizer & test
target_link_libraries(app_visualizer ${wxWidgets_LIBRARIES} lib_silly_objects)
target_link_libraries(test_visualizer ${wxWidgets_LIBRARIES} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} lib_silly_objects)


