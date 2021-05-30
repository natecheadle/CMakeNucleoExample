

project(NUCLEO-${BUILD_TARGET})

enable_language(C ASM)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

set(STM32CUBEMX_GENERATED_FILES
        Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal.c
        Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc.c
        Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc_ex.c
        Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_gpio.c
        Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_dma.c
        Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_cortex.c
        Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pwr.c
        Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pwr_ex.c
        Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_flash.c
        Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_flash_ex.c
        Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c
        Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c_ex.c
        Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_exti.c
        Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_tim.c
        Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_tim_ex.c
        Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart.c
        Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart_ex.c        

        Inc/main.h
        Inc/stm32f3xx_hal_conf.h
        Inc/stm32f3xx_it.h

        Src/main.c
        Src/freertos.c
        Src/stm32f3xx_it.c
        Src/stm32f3xx_hal_msp.c
        Src/stm32f3xx_hal_timebase_tim.c
        Src/system_stm32f3xx.c

        Middlewares/Third_Party/FreeRTOS/Source/croutine.c
        Middlewares/Third_Party/FreeRTOS/Source/event_groups.c
        Middlewares/Third_Party/FreeRTOS/Source/list.c
        Middlewares/Third_Party/FreeRTOS/Source/queue.c
        Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.c
        Middlewares/Third_Party/FreeRTOS/Source/tasks.c
        Middlewares/Third_Party/FreeRTOS/Source/timers.c
        Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.c
        Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c
        Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c

        startup_stm32f303xe.s)

set(EXECUTABLE ${PROJECT_NAME}.out)

add_executable(${EXECUTABLE} ${STM32CUBEMX_GENERATED_FILES})

target_compile_definitions(${EXECUTABLE} PRIVATE
        -DUSE_HAL_DRIVER
        -DSTM32F303xE
        )

target_include_directories(${EXECUTABLE} PRIVATE
        Inc
        Drivers/STM32F3xx_HAL_Driver/Inc
        Drivers/STM32F3xx_HAL_Driver/Inc/Legacy
        Middlewares/Third_Party/FreeRTOS/Source/include
        Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2
        Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F
        Drivers/CMSIS/Device/ST/STM32F3xx/Include
        Drivers/CMSIS/Include
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
