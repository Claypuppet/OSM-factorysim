
file(GLOB lib_network_SRC
        "**.h"
        "**.cpp")

add_library(lib_network SHARED
        ${lib_network_SRC})

target_link_libraries(lib_network lib_utils ${Boost_SYSTEM_LIBRARY})


install(TARGETS
        lib_network
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)