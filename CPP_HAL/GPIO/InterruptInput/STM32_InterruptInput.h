#pragma once

#include <cstdint>
#include <stm32f3xx_hal.h>

#include "IInterruptInput.h"
#include "Pins.h"

namespace CPP_HAL{
    class STM32_InterruptInput : public IInterruptInput
    {
    public:
        STM32_InterruptInput(PIN pin, PULL pull = PULL::NONE);
        ~STM32_InterruptInput();
        bool Read() final;
        void SetOnRiseFunc(std::function<void()> intFunc) final;
        void SetOnFallFunc(std::function<void()> intFunc) final;
    };
}