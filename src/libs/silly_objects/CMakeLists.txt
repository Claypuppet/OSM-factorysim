file(GLOB lib_silly_objects_SRC
        "**.hpp"
        "**.cpp")

add_library(lib_silly_objects SHARED
        ${lib_silly_objects_SRC})

target_link_libraries(lib_silly_objects ${wxWidgets_LIBRARIES} ${Boost_DATE_TIME_LIBRARY})

install(TARGETS
        lib_silly_objects
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)