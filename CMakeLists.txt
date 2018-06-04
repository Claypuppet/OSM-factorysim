cmake_minimum_required(VERSION 3.3)
project(production_line_control)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_CXX_STANDARD 11)

find_package(wxWidgets REQUIRED net gl core base)
include(${wxWidgets_USE_FILE})

find_package(Boost REQUIRED COMPONENTS system unit_test_framework)
link_directories(${Boost_LIBRARY_DIR} )

include_directories(src/libs)
add_subdirectory(src)
add_subdirectory(tests)
