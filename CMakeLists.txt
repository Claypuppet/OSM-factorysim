cmake_minimum_required(VERSION 3.5)
project(production_line_simulator)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")


include_directories(src/lib_network)

find_package(wxWidgets REQUIRED net gl core base)
include(${wxWidgets_USE_FILE})

find_package(Boost REQUIRED COMPONENTS system filesystem unit_test_framework)
link_directories(${Boost_LIBRARY_DIR} )


### SET APPLICATION EXECUTABLES ###

# Add

add_executable(app_machine_simulator
        src/machine_simulator/Main.cpp)

add_executable(app_production_control
        src/production_control/Main.cpp)

add_executable(app_visualizer
        src/visualizer/Main.cpp)


### SET APPLICATION TEST EXECUTABLES ###

add_executable(test_machine_simulator
        tests/machine_simulator/Main.cpp
        tests/machine_simulator/Object_test.cpp)

add_executable(test_production_control
        tests/production_control/Main.cpp
        tests/production_control/Object_test.cpp)

add_executable(test_visualizer
        tests/visualizer/Main.cpp
        tests/visualizer/Object_test.cpp)

### SET APPLICATION LIBRARIES ###

add_library(lib_network STATIC
        src/lib_network/Lib1.cpp
        src/lib_network/Object.cpp
        src/lib_network/BetterObject.cpp)

install(TARGETS lib_network
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)


### LINK LIBRARIES ###

# TODO: remove wxwidget library from lib after project startup, (and change boost to include asio)
target_link_libraries(lib_network ${wxWidgets_LIBRARIES} ${Boost_DATE_TIME_LIBRARY})


# Production control & test
target_link_libraries(app_production_control lib_network)
target_link_libraries(test_production_control ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} lib_network)

# Machine simulator & test
target_link_libraries(app_machine_simulator lib_network)
target_link_libraries(test_machine_simulator ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} lib_network)

# Visualizer & test
target_link_libraries(app_visualizer ${wxWidgets_LIBRARIES} lib_network)
target_link_libraries(test_visualizer ${wxWidgets_LIBRARIES} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} lib_network)


