cmake_minimum_required(VERSION 3.2)
project(CPP_HAL)

include(CppHalSrcs.cmake)

add_library(${PROJECT_NAME} STATIC ${CppHalSrcs})
target_link_libraries(${PROJECT_NAME} st_hal)
target_include_directories(${PROJECT_NAME} PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/inc
)

