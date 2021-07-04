cmake_minimum_required(VERSION 3.2)
project(CPP_HAL)

set(CppHalSrcs
		GPIO/DigitalOut/STM32/STM32_DigitalOut.cpp
		GPIO/DigitalIn/STM32/STM32_DigitalIn.cpp
		src/CPP_HAL.cpp
        GPIO/Pins/STM32_Pin.cpp GPIO/Pins/STM32_Pin.h)

add_library(${PROJECT_NAME} STATIC ${CppHalSrcs})
target_link_libraries(${PROJECT_NAME} st_hal)
target_include_directories(${PROJECT_NAME} PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/inc
)

