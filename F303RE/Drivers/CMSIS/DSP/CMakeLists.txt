project(DSP)

include(DSPSources.cmake)
enable_language(ASM)

add_library(${PROJECT_NAME} STATIC ${cmsis_dsp_sources})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Include/)
target_link_libraries(${PROJECT_NAME} CMSIS)

if(FLOAT_ABI STREQUAL hard)
	target_compile_definitions(${PROJECT_NAME} PRIVATE -D__FPU_PRESENT)
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE -D${STM32_PLATFORM} -DARM_MATH_CM4)