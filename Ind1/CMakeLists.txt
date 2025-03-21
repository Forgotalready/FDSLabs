cmake_minimum_required(VERSION 3.28)
project(Ind1)

find_package(OpenMP REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(Ind1 main.cpp Solver.cpp Solver.h IntegrationMethod/IIntegrateMethod.cpp IntegrationMethod/IIntegrateMethod.h IntegrationMethod/RectangleIntegration.cpp IntegrationMethod/RectangleIntegration.h
        IntegrationMethod/RectangleIntegrationNoParralel.cpp
        IntegrationMethod/RectangleIntegrationNoParralel.h)
if(OpenMP_CXX_FOUND)
    target_link_libraries(Ind1 PRIVATE OpenMP::OpenMP_CXX)
endif()

