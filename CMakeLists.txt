project("CMakeNucleoExample")

cmake_minimum_required(VERSION 3.15.3)

set(BUILD_TARGET "F303RE" CACHE STRING "Target (ex F303RE)")

add_subdirectory(${BUILD_TARGET})