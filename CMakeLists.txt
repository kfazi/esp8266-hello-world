cmake_minimum_required(VERSION 3.15)

set(LOCAL_CFG "" CACHE FILEPATH "Path to local config")
if(NOT LOCAL_CFG)
    message(FATAL_ERROR "LOCAL_CFG variable not set. Use -DLOCAL_CFG=<file> to set local config. See local-example.cmake for available options")
endif()
include(${LOCAL_CFG})

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/toolchain.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/utils.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

project(hello-world)

add_subdirectory(main)
add_subdirectory(sdk)

configure_partitions()
add_flash()
