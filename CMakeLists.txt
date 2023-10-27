cmake_minimum_required(VERSION 3.26)
project(thesis)

set(CMAKE_CXX_STANDARD 17)

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

)
