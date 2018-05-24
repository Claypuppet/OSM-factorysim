file(GLOB lib_yaml_SRC
        "include/yaml-cpp/**.h"
        "src/**.cpp")

add_library(lib_yaml-cpp SHARED
        ${lib_yaml_SRC})

install(TARGETS
        lib_yaml-cpp
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
