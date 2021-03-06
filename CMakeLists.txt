project("CMakeNucleoExample")

cmake_minimum_required(VERSION 3.15.3)

set(BUILD_TARGET "F303RE" CACHE STRING "Target (ex F303RE)")

add_subdirectory(${BUILD_TARGET}/Drivers/CMSIS)
add_subdirectory(${BUILD_TARGET}/Drivers/STM32F3xx_HAL_Driver)

project(NUCLEO-${BUILD_TARGET})

enable_language(C ASM)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

set(STM32CUBEMX_GENERATED_FILES 
        src/main.c
        src/stm32f3xx_it.c
        src/stm32f3xx_hal_msp.c
        src/system_stm32f3xx.c)

set(EXECUTABLE ${PROJECT_NAME}.out)

add_executable(${EXECUTABLE} ${STM32CUBEMX_GENERATED_FILES})

target_include_directories(${EXECUTABLE} PRIVATE inc)
target_link_libraries(${EXECUTABLE} CMSIS stm32f3xx_hal DSP)
        
target_link_options(${EXECUTABLE} PRIVATE
        -T${CMAKE_SOURCE_DIR}/src/STM32F303RETx_FLASH.ld
)

# Print executable size
add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND arm-none-eabi-size ${EXECUTABLE})

# Create hex file
add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND arm-none-eabi-objcopy -O ihex ${EXECUTABLE} ${PROJECT_NAME}.hex
        COMMAND arm-none-eabi-objcopy -O binary ${EXECUTABLE} ${PROJECT_NAME}.bin)