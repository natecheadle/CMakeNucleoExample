project(FREE_RTOS)

include(FreeRTOSSources.cmake)
add_library(${PROJECT_NAME} STATIC ${free_rtos_sources})
target_include_directories(${PROJECT_NAME} PUBLIC 
    Source/include
    Source/CMSIS_RTOS_V2
    Source/portable/GCC/ARM_CM4F)

target_link_libraries(${PROJECT_NAME} CMSIS)

option(USE_FreeRTOS_HEAP_1 "FreeRTOS Heap 1" OFF)
option(USE_FreeRTOS_HEAP_2 "FreeRTOS Heap 2" OFF)
option(USE_FreeRTOS_HEAP_3 "FreeRTOS Heap 3" OFF)
option(USE_FreeRTOS_HEAP_4 "FreeRTOS Heap 4" ON)
option(USE_FreeRTOS_HEAP_5 "FreeRTOS Heap 5" OFF)

configure_file(${PROJECT_SOURCE_DIR}/Source/include/FreeRTOSConfig_template.h ${PROJECT_SOURCE_DIR}/Source/include/FreeRTOSConfig.h)
