file(GLOB_RECURSE lib_patterns_SRC
        "**.h"
        "**.cpp")

add_library(lib_patterns SHARED
        notifyobserver/Notifier.cpp
        notifyobserver/Notifier.hpp
        notifyobserver/Observer.cpp
        notifyobserver/Observer.hpp
        producerconsumer/Queue.cpp
        producerconsumer/Queue.h
        singleton/Singleton.cpp
        singleton/Singleton.h
        statemachine/Context.cpp
        statemachine/Context.h
        statemachine/Event.h
        statemachine/State.h)

target_link_libraries(lib_patterns ${Boost_SYSTEM_LIBRARY})

install(TARGETS
        lib_patterns
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)