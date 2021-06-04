cmake_minimum_required(VERSION 3.2)
project(CMSIS)

include(DSPSources.cmake)

set(STM32_PLATFORM "STM32F303xE" CACHE STRING "Target microprocessor platform")
set_property(CACHE STM32_PLATFORM PROPERTY STRINGS 
	STM32F303xE
)

if(STM32_PLATFORM STREQUAL STM32F3xx)
	set(cmsis_startup stm32f3xx)
elseif(STM32_PLATFORM STREQUAL STM32F301x8)
	set(cmsis_startup stm32f301x8)
elseif(STM32_PLATFORM STREQUAL STM32F302x8)
	set(cmsis_startup stm32f302x8)
elseif(STM32_PLATFORM STREQUAL STM32F302xC)
	set(cmsis_startup stm32f302xc)
elseif(STM32_PLATFORM STREQUAL STM32F302xE)
	set(cmsis_startup stm32f302xE)
elseif(STM32_PLATFORM STREQUAL STM32F303xE)
	set(cmsis_startup stm32f303xe)
elseif(STM32_PLATFORM STREQUAL STM32F318xx)
	set(cmsis_startup stm32f318xx)
elseif(STM32_PLATFORM STREQUAL STM32F328xx)
	set(cmsis_startup stm32f328xx)
elseif(STM32_PLATFORM STREQUAL STM32F334x8)
	set(cmsis_startup stm32f334x8)
elseif(STM32_PLATFORM STREQUAL STM32F358xx)
	set(cmsis_startup stm32f358xx)
elseif(STM32_PLATFORM STREQUAL STM32F373xC)
	set(cmsis_startup stm32f373xc)
elseif(STM32_PLATFORM STREQUAL STM32F378xx)
	set(cmsis_startup stm32f378xx)
elseif(STM32_PLATFORM STREQUAL STM32F398xx)
	set(cmsis_startup stm32f398xx)
endif()

enable_language(ASM)
add_library(${PROJECT_NAME} STATIC 
	Device/ST/STM32F3xx/Source/Templates/gcc/startup_${cmsis_startup}.s 
	Device/ST/STM32F3xx/Source/Templates/system_stm32f3xx.c
	#${cmsis_dsp_sources}
)

target_include_directories(${PROJECT_NAME} PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/Include
	${CMAKE_CURRENT_SOURCE_DIR}/Device/ST/STM32F3xx/Include
	#${CMAKE_CURRENT_SOURCE_DIR}/DSP/Include/
)


if(FLOAT_ABI STREQUAL hard)
	#target_compile_definitions(${PROJECT_NAME} PUBLIC -D__FPU_PRESENT)
endif()

target_compile_definitions(${PROJECT_NAME} PUBLIC -D${STM32_PLATFORM} -DARM_MATH_CM4)
