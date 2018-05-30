add_executable(test_visualizer
        Main.cpp
        Object_test.cpp FileReaderTests.cpp)

target_link_libraries(test_visualizer source_lib_app_visualizer lib_test_utils ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
