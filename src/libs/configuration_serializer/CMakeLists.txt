file(GLOB_RECURSE lib_configuration_serializer_SRC
        "**.h"
        "**.cpp")

add_library(lib_configuration_serializer SHARED
        ${lib_configuration_serializer_SRC})

target_link_libraries(lib_configuration_serializer lib_yaml-cpp)

install(TARGETS
        lib_configuration_serializer
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)