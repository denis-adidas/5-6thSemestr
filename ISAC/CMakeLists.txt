cmake_minimum_required(VERSION 3.26.4)
project(ISIS)

set(CMAKE_CXX_STANDARD 17)

add_executable(ISIS
        main.cpp
        term.cpp
        term.hpp
        util.cpp
        util.hpp
        #        test.cpp
)
