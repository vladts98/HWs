cmake_minimum_required (VERSION 3.8)

project("11.5")
add_library(Class SHARED Figures.cpp Figures.h print_info.cpp print_info.h)
add_executable (figures 6.3.cpp)

target_link_libraries(figures Class)