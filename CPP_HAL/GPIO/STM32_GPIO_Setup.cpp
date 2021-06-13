#include "STM32_GPIO_Setup.h"

namespace CPP_HAL {
    bool STM32_GPIO_Setup::IsInitialized = false;

    void STM32_GPIO_Setup::InitClock()
    {
        if(!IsInitialized)
        {
            __HAL_RCC_GPIOC_CLK_ENABLE();
            __HAL_RCC_GPIOF_CLK_ENABLE();
            __HAL_RCC_GPIOA_CLK_ENABLE();
            __HAL_RCC_GPIOB_CLK_ENABLE();
        }
    }
}
