add_library(lib_test_utils SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/MockNetwork.h
        ${CMAKE_CURRENT_SOURCE_DIR}/MockNetwork.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MockObserver.h
        ${CMAKE_CURRENT_SOURCE_DIR}/MockObserver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/HelperFunctions.h
        ${CMAKE_CURRENT_SOURCE_DIR}/HelperFunctions.cpp)