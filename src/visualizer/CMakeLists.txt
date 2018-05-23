add_library(source_lib_app_visualizer SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/Window.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Window.h
        )

target_link_libraries(source_lib_app_visualizer ${wxWidgets_LIBRARIES} lib_silly_objects)


add_executable(app_visualizer
        ${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp)


target_link_libraries(app_visualizer source_lib_app_visualizer)
