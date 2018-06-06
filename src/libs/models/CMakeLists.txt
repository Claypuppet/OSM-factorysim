file(GLOB lib_models_SRC
        "**.h"
        "**.cpp")

add_library(lib_models SHARED
        ${lib_models_SRC} PostProcessInfo.cpp PostProcessInfo.h)

install(TARGETS
        lib_models
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
