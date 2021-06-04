cmake_minimum_required(VERSION 3.2)

project(CMSIS_DSP)


add_library(${PROJECT_NAME} STATIC ${cmsis_dsp_sources})

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/
    ${CMAKE_CURRENT_SOURCE_DIR}/../Include/)

target_compile_definitions(${PROJECT_NAME} PUBLIC -DARM_MATH_CM4)