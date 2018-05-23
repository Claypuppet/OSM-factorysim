
### SET APPLICATION LIBRARIES ###

# Lib Network
file(GLOB lib_network_SRC
        "network/**.h"
        "network/**.cpp")

add_library(lib_network SHARED
        ${lib_network_SRC})

# Lib Models
file(GLOB lib_models_SRC
        "models/**.h"
        "models/**.cpp")

add_library(lib_models SHARED
        ${lib_models_SRC})

# Lib Patterns
file(GLOB_RECURSE lib_patterns_SRC
        "patterns/**.h"
        "patterns/**.cpp")

add_library(lib_patterns SHARED
        ${lib_patterns_SRC})

# Lib yaml-cpp
file(GLOB lib_yaml_SRC
        "yaml-cpp/include/yaml-cpp/**.h"
        "yaml-cpp/src/**.cpp")

add_library(lib_yaml-cpp SHARED
        ${lib_yaml_SRC})

# Lib Cereal
file(GLOB lib_cereal_SRC
        "cereal/**.hpp")

add_library(lib_cereal INTERFACE)
target_sources(lib_cereal INTERFACE ${lib_cereal_SRC})


# Lib Silly objects
file(GLOB lib_silly_objects_SRC
        "silly_objects/**.hpp"
        "silly_objects/**.cpp")

add_library(lib_silly_objects SHARED
        ${lib_silly_objects_SRC})

# Lib utils
file(GLOB lib_utils_SRC
        "utils/**.h"
        "utils/**.cpp"
        "utils/time/**.h"
        "utils/time/**.cpp")

add_library(lib_utils SHARED
        ${lib_utils_SRC})


## Libs
target_link_libraries(lib_silly_objects ${wxWidgets_LIBRARIES} ${Boost_DATE_TIME_LIBRARY})
target_link_libraries(lib_patterns ${Boost_SYSTEM_LIBRARY})
target_link_libraries(lib_utils lib_patterns)
target_link_libraries(lib_network lib_utils ${Boost_SYSTEM_LIBRARY})
target_link_libraries(lib_models lib_yaml-cpp)


install(TARGETS
        lib_silly_objects
        lib_network
        lib_patterns
        lib_yaml-cpp
        lib_models
        lib_utils
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)