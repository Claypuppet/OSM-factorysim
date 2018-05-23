add_executable(test_visualizer
        ${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Object_test.cpp)

target_link_libraries(test_visualizer source_lib_app_visualizer lib_test_utils ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
