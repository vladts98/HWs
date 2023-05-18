cmake_minimum_required (VERSION 3.8)

project("Final")

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
add_library(Race SHARED Race.h Race.cpp)
add_library(Vehicles SHARED Vehicles.h Vehicles.cpp)
add_executable (final_project main.cpp)

target_link_libraries(Race PUBLIC Vehicles)
target_link_libraries(final_project PUBLIC Race)