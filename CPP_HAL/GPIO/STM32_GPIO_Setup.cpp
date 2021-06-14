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

    GPIO_TypeDef* STM32_GPIO_Setup::GetHALPort(PIN pin)
    {
        switch (pin)
        {
        case PIN::PA_0:
        case PIN::PA_1:
        case PIN::PA_2:
        case PIN::PA_3:
        case PIN::PA_4:
        case PIN::PA_5:
        case PIN::PA_6:
        case PIN::PA_7:
        case PIN::PA_8:
        case PIN::PA_9:
        case PIN::PA_10:
        case PIN::PA_11:
        case PIN::PA_12:
        case PIN::PA_13:
        case PIN::PA_14:
        case PIN::PA_15:
            return GPIOA;
        case PIN::PB_0:
        case PIN::PB_1:
        case PIN::PB_2:
        case PIN::PB_3:
        case PIN::PB_4:
        case PIN::PB_5:
        case PIN::PB_6:
        case PIN::PB_7:
        case PIN::PB_8:
        case PIN::PB_9:
        case PIN::PB_10:
        case PIN::PB_11:
        case PIN::PB_12:
        case PIN::PB_13:
        case PIN::PB_14:
        case PIN::PB_15:
            return GPIOB;
        case PIN::PC_0:
        case PIN::PC_1:
        case PIN::PC_2:
        case PIN::PC_3:
        case PIN::PC_4:
        case PIN::PC_5:
        case PIN::PC_6:
        case PIN::PC_7:
        case PIN::PC_8:
        case PIN::PC_9:
        case PIN::PC_10:
        case PIN::PC_11:
        case PIN::PC_12:
        case PIN::PC_13:
        case PIN::PC_14:
        case PIN::PC_15:
            return GPIOC;
        }

        return nullptr;
    }

    uint32_t STM32_GPIO_Setup::GetHALPin(PIN pin)
    {
        switch(pin)
        {
        case PIN::PA_0:
        case PIN::PB_0:
        case PIN::PC_0:
            return GPIO_PIN_0;
        case PIN::PA_1:
        case PIN::PB_1:
        case PIN::PC_1:
            return GPIO_PIN_1;
        case PIN::PA_2:
        case PIN::PB_2:
        case PIN::PC_2:
            return GPIO_PIN_2;
        case PIN::PA_3:
        case PIN::PB_3:
        case PIN::PC_3:
            return GPIO_PIN_3;
        case PIN::PA_4:
        case PIN::PB_4:
        case PIN::PC_4:
            return GPIO_PIN_4;
        case PIN::PA_5:
        case PIN::PB_5:
        case PIN::PC_5:
            return GPIO_PIN_5;
        case PIN::PA_6:
        case PIN::PB_6:
        case PIN::PC_6:
            return GPIO_PIN_6;
        case PIN::PA_7:
        case PIN::PB_7:
        case PIN::PC_7:
            return GPIO_PIN_7;
        case PIN::PA_8:
        case PIN::PB_8:
        case PIN::PC_8:
            return GPIO_PIN_8;
        case PIN::PA_9:
        case PIN::PB_9:
        case PIN::PC_9:
            return GPIO_PIN_9;
        case PIN::PA_10:
        case PIN::PB_10:
        case PIN::PC_10:
            return GPIO_PIN_10;
        case PIN::PA_11:
        case PIN::PB_11:
        case PIN::PC_11:
            return GPIO_PIN_11;
        case PIN::PA_12:
        case PIN::PB_12:
        case PIN::PC_12:
            return GPIO_PIN_12;
        case PIN::PA_13:
        case PIN::PB_13:
        case PIN::PC_13:
            return GPIO_PIN_13;
        case PIN::PA_14:
        case PIN::PB_14:
        case PIN::PC_14:
            return GPIO_PIN_14;
        case PIN::PA_15:
        case PIN::PB_15:
        case PIN::PC_15:
            return GPIO_PIN_15;
        }

        return 0;
    }
}
