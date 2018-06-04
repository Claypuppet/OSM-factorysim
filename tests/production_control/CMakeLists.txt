add_executable(test_production_control
        Main.cpp
        controller_test.cpp
        log_test.cpp
        application_test.cpp)

target_link_libraries(test_production_control source_lib_app_production lib_test_utils ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_custom_target(test_config_mover ALL
        DEPENDS move_test_config)

add_custom_command(OUTPUT move_test_config
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/tests/production_control/test_configs" ${CMAKE_CURRENT_BINARY_DIR}/test_configs)

add_dependencies(test_production_control test_config_mover)
