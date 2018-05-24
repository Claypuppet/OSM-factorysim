add_executable(test_production_control
        Main.cpp
        controller_test.cpp
        log_test.cpp
        application_test.cpp)


target_link_libraries(test_production_control source_lib_app_production lib_test_utils ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})


add_custom_command(TARGET test_production_control PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/tests/production_control/test_configs" $<TARGET_FILE_DIR:test_production_control>/test_configs)
