add_executable(test_machine_control
        Main.cpp
        Object_test.cpp
        controller_test.cpp
        Network_test.cpp
        Application_test.cpp)

target_link_libraries(test_machine_control source_lib_app_machine_control lib_models lib_test_utils ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})