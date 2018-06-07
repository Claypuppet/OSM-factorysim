
add_library(lib_network SHARED
        Message.h
        Manager.cpp
        Connection.h
        Connection.cpp
        Client.cpp
        Client.h
        Server.h
        Manager.h
        Protocol.h
        Server.cpp)

target_link_libraries(lib_network lib_utils ${Boost_SYSTEM_LIBRARY})


install(TARGETS
        lib_network
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)