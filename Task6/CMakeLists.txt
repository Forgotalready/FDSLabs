cmake_minimum_required(VERSION 3.28)
project(Task5)

find_package(OpenMP REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(Task6 main.cpp)

if(OpenMP_CXX_FOUND)
    target_link_libraries(Task6 PRIVATE OpenMP::OpenMP_CXX)
endif()
