cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()


#Set the project name
project(SolvingHeatEquation)

# Find all the source files in the project directory
file(GLOB SOURCES *.cpp)

#Add the executable
add_executable(SolvingHeatEquation ${SOURCES})