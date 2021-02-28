cmake_minimum_required(VERSION 3.17)
project(MykhLab6)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-luuid")
# using pkg-config to configure uuid
find_package(PkgConfig REQUIRED)
find_package(Threads REQUIRED)

pkg_search_module(UUID SHARED uuid)

add_executable(MykhLab6 main.cpp Timer.cpp Timer.h Watch.cpp Watch.h Helpers.cpp Helpers.h)

target_link_libraries(MykhLab6 Threads::Threads)
