file(GLOB lib_utils_SRC
        "**.h"
        "**.cpp"
        "time/**.h"
        "time/**.cpp")

add_library(lib_utils SHARED
        ${lib_utils_SRC})

target_link_libraries(lib_utils lib_patterns)

install(TARGETS
        lib_utils
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
