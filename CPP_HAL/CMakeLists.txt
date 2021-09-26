cmake_minimum_required(VERSION 3.2)
project(CPP_HAL)

set(CppHalSrcs
        src/CPP_HAL.cpp
        GPIO/DigitalOut/STM32/STM32_DigitalOut.cpp
        GPIO/DigitalIn/STM32/STM32_DigitalIn.cpp
        GPIO/Pins/STM32_Pin.cpp
        Serial/USART/STM32/STM32_SynchronousUSART.cpp
        Serial/USART/STM32/STM32_AsynchronousUSART.cpp)

add_library(${PROJECT_NAME} STATIC ${CppHalSrcs})
target_link_libraries(${PROJECT_NAME} STM32_F3_HAL Shared_Lib)
target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
        )

