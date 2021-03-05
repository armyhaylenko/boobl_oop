cmake_minimum_required(VERSION 3.17)
project(MykhLab6)

set(CMAKE_CXX_STANDARD 20)

find_package(Threads REQUIRED)

add_executable(MykhLab6 main.cpp Timer.cpp Timer.h Watch.cpp Watch.h Helpers.cpp Helpers.h)

target_link_libraries(MykhLab6 Threads::Threads)
