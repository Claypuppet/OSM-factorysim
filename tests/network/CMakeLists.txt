add_executable(test_network
        ${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/network_test.cpp)

target_link_libraries(test_network lib_network lib_models lib_test_utils ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})