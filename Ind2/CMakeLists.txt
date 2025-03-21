cmake_minimum_required(VERSION 3.28)
project(Ind2)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenMP REQUIRED)

add_executable(Ind2 main.cpp)

if(OpenMP_CXX_FOUND)
    target_link_libraries(Ind2 PRIVATE OpenMP::OpenMP_CXX)
endif()