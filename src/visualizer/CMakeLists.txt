add_library(source_lib_app_visualizer SHARED
        Window.cpp
        Window.h
        )

target_link_libraries(source_lib_app_visualizer ${wxWidgets_LIBRARIES} lib_silly_objects)


add_executable(app_visualizer
        Main.cpp)


target_link_libraries(app_visualizer source_lib_app_visualizer)
