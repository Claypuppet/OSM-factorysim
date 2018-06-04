file(GLOB_RECURSE lib_patterns_SRC
        "**.h"
        "**.cpp")

add_library(lib_patterns SHARED
        ${lib_patterns_SRC})

target_link_libraries(lib_patterns ${Boost_SYSTEM_LIBRARY})

install(TARGETS
        lib_patterns
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)