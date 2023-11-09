cmake_minimum_required(VERSION 3.26)
project(lab02)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab02 main.cpp
        RC6.cpp
        RC6.hpp
        Util.cpp
        Util.hpp
        analysis.cpp
        analysis.hpp
)
