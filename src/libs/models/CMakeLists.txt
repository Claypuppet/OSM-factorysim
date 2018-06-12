add_library(lib_models SHARED
        Configuration.cpp
        Configuration.h
        Machine.cpp
        Machine.h
        MachineConfiguration.cpp
        MachineConfiguration.h
        MachineStatistics.cpp
        MachineStatistics.h
        MachineFinalStatistics.h
        MachineFinalStatistics.cpp
        PostProcessInfo.cpp
        PostProcessInfo.h
        PreviousMachine.cpp
        PreviousMachine.h
        Product.cpp
        Product.h
        ProductionLine.cpp
        ProductionLine.h
        SimulationInfo.cpp
        SimulationInfo.h
        PostProcessInfo.cpp
        PostProcessInfo.h
        MachineProductStatistics.cpp
        MachineProductStatistics.h
        MachineProductFinalStatistics.cpp
        MachineProductFinalStatistics.h)

install(TARGETS
        lib_models
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
