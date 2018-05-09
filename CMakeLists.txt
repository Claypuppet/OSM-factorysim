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

# Add CMakeLists from sub directories

add_subdirectory(src/visualizer)
add_subdirectory(src/machine_control)
add_subdirectory(src/production_control)

# Add executables

add_executable(app_machine_control
        src/machine_control/Main.cpp
        ${app_machine_control_SOURCES} src/machine_control/states_simulation/WaitForProductControlState.cpp src/machine_control/states_simulation/WaitForProductControlState.h)


add_executable(app_production_control
        src/production_control/Main.cpp
        ${app_production_control_SOURCES})


add_executable(app_visualizer
        src/visualizer/Main.cpp
        ${app_visualizer_SOURCES})


### SET APPLICATION TEST EXECUTABLES ###

# Add tests, including the sources of the executable

add_subdirectory(tests/test_helpers)

add_executable(test_machine_control
        ${test_helpers_SOURCES}
        ${app_machine_control_SOURCES}
        tests/machine_control/Main.cpp
        tests/machine_control/Object_test.cpp)

add_executable(test_production_control
        ${test_helpers_SOURCES}
        ${app_production_control_SOURCES}
        tests/production_control/Main.cpp
        tests/production_control/controller_test.cpp)

add_executable(test_visualizer
#        ${test_helpers_SOURCES}
        ${app_visualizer_SOURCES}
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

# Lib utils
file(GLOB lib_utils_SRC
        "src/libs/utils/**.h"
        "src/libs/utils/**.cpp")

add_library(lib_utils SHARED
        ${lib_utils_SRC})


install(TARGETS
        lib_silly_objects
        lib_network
        lib_patterns
        lib_yaml-cpp
        lib_models
        lib_utils
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)


### LINK LIBRARIES ###

# Libs
target_link_libraries(lib_silly_objects ${wxWidgets_LIBRARIES} ${Boost_DATE_TIME_LIBRARY})
target_link_libraries(lib_patterns ${Boost_SYSTEM_LIBRARY})
target_link_libraries(lib_utils lib_patterns)
target_link_libraries(lib_network lib_utils ${Boost_SYSTEM_LIBRARY})
target_link_libraries(lib_models lib_yaml-cpp)

# Applications
target_link_libraries(app_production_control lib_yaml-cpp lib_models lib_network lib_patterns lib_utils)
target_link_libraries(app_machine_control lib_network lib_patterns lib_models)
target_link_libraries(app_visualizer ${wxWidgets_LIBRARIES} lib_silly_objects)

# Tests
target_link_libraries(test_production_control lib_yaml-cpp lib_models lib_network lib_patterns lib_utils ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
target_link_libraries(test_machine_control lib_network lib_patterns lib_models ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} lib_silly_objects)
target_link_libraries(test_visualizer lib_silly_objects ${wxWidgets_LIBRARIES} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

### Move config files

# For production control, move configuration dir to bin dir
add_custom_command(TARGET app_production_control POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/configs" $<TARGET_FILE_DIR:app_production_control>/configs)

# For testing prod control, move test configs to bin dir
add_custom_command(TARGET test_production_control POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/tests/production_control/test_configs" $<TARGET_FILE_DIR:test_production_control>/test_configs)
