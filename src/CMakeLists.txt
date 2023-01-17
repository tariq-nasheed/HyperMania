# Basic CMake that uses All.c
cmake_minimum_required(VERSION 3.7)

project(hypermania)
set(CMAKE_STATIC_LIBRARY_PREFIX "")

set(CMAKE_C_FLAGS "-O2")
set(CMAKE_CXX_FLAGS "-O2")
set(MOD_NAME hypermania CACHE STRING "The mod directory to look into")
set(OUTPUT_NAME "hypermania" CACHE STRING "The name of the built library")

add_library(hypermania SHARED
    GameAPI/C/GameAPI/Game.c
    ${MOD_NAME}/util.c
    ${MOD_NAME}/dllmain.c
    ${MOD_NAME}/Objects/All.c
)

target_include_directories(hypermania PRIVATE
    ${MOD_NAME}/
    ${MOD_NAME}/Objects/
    ${MOD_NAME}/Objects/Boilerplate
    GameAPI/C/
)

set_target_properties(hypermania PROPERTIES OUTPUT_NAME ${OUTPUT_NAME})

unset(MOD_NAME CACHE)
unset(OUTPUT_NAME CACHE)
