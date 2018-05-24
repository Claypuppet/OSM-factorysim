file(GLOB lib_models_SRC
        "**.h"
        "**.cpp")

add_library(lib_models SHARED
        ${lib_models_SRC})

target_link_libraries(lib_models lib_yaml-cpp)

install(TARGETS
        lib_models
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
