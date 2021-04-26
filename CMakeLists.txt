cmake_minimum_required(VERSION 3.15.3)

set(TARGET F303RE)
set(OPT "-Og")

project(nucleo-${TARGET})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(HAL_DRIVER_SRCS
        ${TARGET}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_tim.c
        ${TARGET}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_tim_ex.c
        ${TARGET}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart.c
        ${TARGET}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart_ex.c
        ${TARGET}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal.c
        ${TARGET}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc.c
        ${TARGET}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc_ex.c
        ${TARGET}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_gpio.c
        ${TARGET}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_dma.c
        ${TARGET}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_cortex.c
        ${TARGET}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pwr.c
        ${TARGET}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pwr_ex.c
        ${TARGET}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_flash.c
        ${TARGET}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_flash_ex.c
        ${TARGET}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c
        ${TARGET}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c_ex.c
        ${TARGET}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_exti.c
        )

set(C_SOURCES 
        ${TARGET}/Src/main.c
        ${TARGET}/Src/stm32f3xx_hal_msp.c
        ${TARGET}/Src/stm32f3xx_it.c

        ${TARGET}/Src/system_stm32f3xx.c
)

set(ASM_SOURCES ${TARGET}/startup_stm32f303xe.s)

set(STM32CUBEMX_GENERATED_FILES ${HAL_DRIVER_SRCS} ${C_SOURCES} ${ASM_SOURCES})

set(EXECUTABLE ${PROJECT_NAME}.out)

add_executable(${EXECUTABLE} 
        ${STM32CUBEMX_GENERATED_FILES}
        src/application.cpp)

set(C_DEFS -DUSE_HAL_DRIVER -DSTM32F303xE)

target_compile_definitions(${EXECUTABLE} PRIVATE ${C_DEFS})

target_include_directories(${EXECUTABLE} PRIVATE
        ${TARGET}/Inc
        ${TARGET}/Drivers/STM32F3xx_HAL_Driver/Inc
        ${TARGET}/Drivers/CMSIS/Device/ST/STM32F3xx/Include
        ${TARGET}/Drivers/CMSIS/Include
        inc/
        )

set(CPU -mcpu=cortex-m4)
set(FPU -mfpu=fpv4-sp-d16)
set(FLOAT_ABI -mfloat-abi=hard)
set(MCU ${CPU} -mthumb ${FPU} ${FLOAT_ABI})

target_compile_options(${EXECUTABLE} PRIVATE
        ${MCU}

        -fdata-sections
        -ffunction-sections
        -fno-exceptions

        -Wall

        $<$<CONFIG:Debug>:${OPT}>
        )

target_link_options(${EXECUTABLE} PRIVATE
        -T${CMAKE_SOURCE_DIR}/${TARGET}/STM32${TARGET}Tx_FLASH.ld
        ${MCU}
        -specs=nano.specs
        -lc
        -lm
        -lnosys
        -Wl,-Map=${PROJECT_NAME}.map,--cref
        -Wl,--gc-sections
        -Wl,--print-memory-usage
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
