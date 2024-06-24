cmake_minimum_required(VERSION 3.21)

project(OpenJoystick)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable c++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug" OR ${CMAKE_BUILD_TYPE} STREQUAL RelWithDebInfo)
  add_compile_definitions("_GLIBCXX_DEBUG")
endif()

set(MAIN_FOLDER "${OpenJoystick_SOURCE_DIR}/src")

if(MSVC)
  add_definitions(/MP)
endif()

# set(CMAKE_CXX_FLAGS "-Wall")
if(WIN32)
set(CMAKE_CXX_FLAGS_DEBUG "/ZI /Od")
set(CMAKE_CXX_FLAGS_RELEASE "/O2")
else(WIN32)
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif(WIN32)

add_subdirectory("${MAIN_FOLDER}/lib")
add_subdirectory("${MAIN_FOLDER}/exe")

option(OPENJOYSTICK_BUILD_EXE ON)
if (OPENJOYSTICK_BUILD_EXE)
endif()