cmake_minimum_required(VERSION 3.15.3)

project(nucleo-f303re)

enable_language(C ASM)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)


set(STM32CUBEMX_GENERATED_FILES

        F303RE/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_tim.c 
        F303RE/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_tim_ex.c 
        F303RE/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart.c 
        F303RE/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart_ex.c 
        F303RE/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal.c 
        F303RE/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc.c 
        F303RE/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc_ex.c 
        F303RE/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_gpio.c 
        F303RE/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_dma.c 
        F303RE/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_cortex.c 
        F303RE/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pwr.c 
        F303RE/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pwr_ex.c 
        F303RE/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_flash.c 
        F303RE/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_flash_ex.c 
        F303RE/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c 
        F303RE/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c_ex.c 
        F303RE/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_exti.c 

        F303RE/Inc/main.h
        F303RE/Inc/stm32f3xx_hal_conf.h
        F303RE/Inc/stm32f3xx_it.h

        F303RE/Src/main.c
        F303RE/Src/stm32f3xx_hal_msp.c
        F303RE/Src/stm32f3xx_it.c
        F303RE/Src/system_stm32f3xx.c

        F303RE/startup_stm32f303xe.s)

set(EXECUTABLE ${PROJECT_NAME}.out)

add_executable(${EXECUTABLE} ${STM32CUBEMX_GENERATED_FILES})

target_compile_definitions(${EXECUTABLE} PRIVATE
        -DUSE_HAL_DRIVER
        -DSTM32F303xE
        )

target_include_directories(${EXECUTABLE} PRIVATE
        F303RE/Inc
        F303RE/Drivers/STM32F3xx_HAL_Driver/Inc
        F303RE/Drivers/CMSIS/Device/ST/STM32F3xx/Include
        F303RE/Drivers/CMSIS/Include
        )

target_compile_options(${EXECUTABLE} PRIVATE
        -mcpu=cortex-m4
        -mthumb
        -mfpu=fpv4-sp-d16
        -mfloat-abi=hard

        -fdata-sections
        -ffunction-sections

        -Wall

        $<$<CONFIG:Debug>:-Og>
        )

target_link_options(${EXECUTABLE} PRIVATE
        -T${CMAKE_SOURCE_DIR}/F303RE/STM32F303RETx_FLASH.ld
        -mcpu=cortex-m4
        -mthumb
        -mfpu=fpv4-sp-d16
        -mfloat-abi=hard
        -specs=nano.specs
        -lc
        -lm
        -lnosys
        -Wl,-Map=${PROJECT_NAME}.map,--cref
        -Wl,--gc-sections
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
