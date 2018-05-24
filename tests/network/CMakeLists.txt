add_executable(test_network
        Main.cpp
        network_test.cpp)

target_link_libraries(test_network lib_network lib_models lib_test_utils ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})