cmake_minimum_required(VERSION 3.2)

project(CMSIS_DSP)

include(DSPSources.cmake)
add_library(${PROJECT_NAME} STATIC ${cmsis_dsp_sources})

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/
    ${CMAKE_CURRENT_SOURCE_DIR}/../Include/)
if(FLOAT_ABI STREQUAL hard)
	target_compile_definitions(${PROJECT_NAME} PUBLIC -D__FPU_PRESENT)
endif()
target_compile_definitions(${PROJECT_NAME} PUBLIC -DARM_MATH_CM4)