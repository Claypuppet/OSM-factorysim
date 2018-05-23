add_executable(test_machine_control
        ${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Object_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/controller_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Network_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Application_test.cpp)

target_link_libraries(test_machine_control source_lib_app_machine_control lib_models lib_test_utils ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})