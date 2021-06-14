#include <stm32f3xx_hal.h>
#include "Pins.h"

namespace CPP_HAL {
    class STM32_GPIO_Setup
    {
        static bool IsInitialized;
    public:
        static void InitClock();
        static GPIO_TypeDef* GetHALPort(PIN pin);
        static uint32_t GetHALPin(PIN pin);
    };
}