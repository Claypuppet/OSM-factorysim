add_library(source_lib_app_visualizer SHARED
        application_states/ApplicationState.cpp
        application_states/ApplicationState.h
        application_states/live_states/LiveState.cpp
        application_states/live_states/LiveState.h
        application_states/live_states/ConnectState.cpp
        application_states/live_states/ConnectState.h
        application_states/live_states/LiveConfigureState.cpp
        application_states/live_states/LiveConfigureState.h
        application_states/live_states/ListenState.cpp
        application_states/live_states/ListenState.h
        application_states/file_states/FileState.cpp
        application_states/file_states/FileState.h
        application_states/file_states/FileConfigureState.cpp
        application_states/file_states/FileConfigureState.h
        application_states/file_states/ReadState.cpp
        application_states/file_states/ReadState.h
        application_states/file_states/PlayState.cpp
        application_states/file_states/PlayState.h
        Application.cpp
        Application.h
        Machine.cpp
        Machine.h
        FileReader.cpp
        FileReader.h
        FileApplication.cpp
        FileApplication.h
        LiveApplication.cpp
        LiveApplication.h
        LiveNetwork.cpp
        LiveNetwork.h
        MachineView.cpp
        MachineView.h
        Canvas.cpp
        Canvas.h
        MainWindow.cpp
        MainWindow.h
        WindowApplication.cpp
        WindowApplication.h
        Events/Event.cpp
        Events/Event.h
        Events/StatusUpdateEvent.cpp
        Events/StatusUpdateEvent.h
        Events/ConfigUpdateEvent.cpp
        Events/ConfigUpdateEvent.h
        Events/BufferUpdateEvent.cpp
        Events/BufferUpdateEvent.h)

target_link_libraries(source_lib_app_visualizer ${wxWidgets_LIBRARIES} lib_models lib_network lib_patterns lib_utils lib_yaml-cpp lib_configuration_serializer)

add_executable(app_visualizer
        Main.cpp)

target_link_libraries(app_visualizer source_lib_app_visualizer)