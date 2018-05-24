file(GLOB lib_cereal_SRC
        "**.hpp")

add_library(lib_cereal INTERFACE)

target_sources(lib_cereal INTERFACE ${lib_cereal_SRC})
