cmake_minimum_required (VERSION 3.8)

project("Leaver_project")

add_library(Leaver SHARED Leaver.cpp Leaver.h)
add_executable (Leave L11.2.cpp)
target_link_libraries(Leave Leaver)