cmake_minimum_required(VERSION 3.5.0)

project(Oceanic VERSION 0.1.0)
project(Oceanic C CXX)

set(SOURCE_DIR src)

file(GLOB SOURCES ${SOURCE_DIR}/*.cpp ${SOURCE_DIR}/app/*.cpp ${SOURCE_DIR}/core/*.cpp)

option(OCEANIC_LINUX "Build for Linux" OFF)
option(OCEANIC_MAC "Build for macOS" OFF)
option(OCEANIC_WIN32 "Build for Windows 32-bit" OFF)
option(OCEANIC_WIN64 "Build for Windows 64-bit" OFF)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_executable(Oceanic ${SOURCES})

target_include_directories(Oceanic PRIVATE src)
target_include_directories(Oceanic PRIVATE vendor)

if(OCEANIC_LINUX)
    message(STATUS "Building for Linux")
    add_subdirectory(vendor/linux/SDL3 EXCLUDE_FROM_ALL)
    target_link_libraries(Oceanic PRIVATE SDL3::SDL3)
    target_compile_definitions(Oceanic PRIVATE OCEANIC_LINUX=1)
elseif(OCEANIC_MAC)
    message(STATUS "Building for macOS")
    target_compile_definitions(Oceanic PRIVATE OCEANIC_MAC=1)
elseif(OCEANIC_WIN32)
    message(STATUS "Building for Windows 32-bit")
    target_compile_definitions(Oceanic PRIVATE OCEANIC_WIN32=1)
elseif(OCEANIC_WIN64)
    message(STATUS "Building for Windows 64-bit")
    target_compile_definitions(Oceanic PRIVATE OCEANIC_WIN64=1)
else()
    message(FATAL_ERROR "No platform selected! Please specify a platform using -DOCEANIC_[PLATFORM]=ON")
endif()
