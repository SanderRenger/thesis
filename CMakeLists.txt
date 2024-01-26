cmake_minimum_required(VERSION 3.26)
project(thesis)

set(CMAKE_CXX_STANDARD 17)
MATH(EXPR stack_size "1024 * 1024 * 1024") # 16 Mb
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")
add_executable(thesis main.cpp
        STInt.cpp
        STint.h
        Neuron.cpp
        Neuron.h
        NeuronCluster.cpp
        NeuronCluster.h
        system.h
        system.cpp
        system.cpp
        event.cpp
        filereader.cpp
        filereader.h
        filewriter.cpp
        filewriter.h

)
