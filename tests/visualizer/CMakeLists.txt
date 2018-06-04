add_executable(test_visualizer
        Main.cpp
        Object_test.cpp
        FileReaderTests.cpp)

target_link_libraries(test_visualizer source_lib_app_visualizer lib_test_utils ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_custom_target(test_results_mover ALL
        DEPENDS move_test_results)

add_custom_command(OUTPUT move_test_results
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/tests/visualizer/test_results" ${CMAKE_CURRENT_BINARY_DIR}/test_results)

add_dependencies(test_visualizer test_results_mover)
