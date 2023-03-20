cmake_minimum_required(VERSION 3.20)
project(MyProject1)
add_executable(MyProject1 main.cpp)

add_subdirectory(C:/libs/libpqxx-7.7.4 libpqxx-build)
target_compile_features(MyProject1 PRIVATE cxx_std_17)  # Включите C++17
target_link_libraries(MyProject1 pqxx)