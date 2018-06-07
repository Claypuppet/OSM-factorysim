
add_library(lib_utils SHARED
        time/CustomTime.cpp
        time/CustomTime.h
        time/SystemTime.cpp
        time/SystemTime.h
        time/Time.cpp
        time/Time.h
        CommandLineArguments.cpp
        CommandLineArguments.h
        FileLogger.cpp
        FileLogger.h
        Logger.cpp
        Logger.h)

target_link_libraries(lib_utils lib_patterns)

install(TARGETS
        lib_utils
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
