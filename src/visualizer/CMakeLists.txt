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
        main_window_states/NeutralState.cpp
        main_window_states/NeutralState.h
        main_window_states/LiveFeedState.cpp
        main_window_states/LiveFeedState.h
        main_window_states/FileFeedState.cpp
        main_window_states/FileFeedState.h
        Application.cpp
        Application.h
        Event.cpp
        Event.h
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
        main_window_states/MainWindowState.cpp
        main_window_states/MainWindowState.h
        WindowApplication.cpp
        WindowApplication.h StatusUpdateEvent.cpp StatusUpdateEvent.h ConfigUpdateEvent.cpp ConfigUpdateEvent.h BufferUpdateEvent.cpp BufferUpdateEvent.h)

target_link_libraries(source_lib_app_visualizer ${wxWidgets_LIBRARIES} lib_models lib_network lib_patterns lib_utils lib_yaml-cpp)

add_executable(app_visualizer
        Main.cpp)

target_link_libraries(app_visualizer source_lib_app_visualizer)