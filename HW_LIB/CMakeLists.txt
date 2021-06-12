cmake_minimum_required(VERSION 3.2)
project(HW_LIB)

include(HW_LIB_SOURCES.cmake)

add_library(${PROJECT_NAME} STATIC ${hw_lib_sources})
target_link_libraries(${PROJECT_NAME} stm32f3xx_hal)
target_include_directories(${PROJECT_NAME} PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/DigitalOutput/
)

