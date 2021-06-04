cmake_minimum_required(VERSION 3.20)

project(NUCLEO-${BUILD_TARGET})

enable_language(C ASM)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

add_subdirectory(Middlewares)
add_subdirectory(Drivers)

