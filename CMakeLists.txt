cmake_minimum_required(VERSION 3.26)
project(Ballistics04 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(Ballistics04 main.c
        ballisticCalc.c ballisticCalc.h man.c man.h main.h net.c net.h host.c host.h)
