#pragma once

#include <cstdint>
#include <stm32f3xx_hal.h>

#include "IDigitalIn.h"

namespace CPP_HAL{
    class STM32_DigitalIn : public IDigitalIn 
    {
        STM32_DigitalIn();
        virtual ~STM32_DigitalIn() = default;
        bool Read() final;
        void AssignInterrupt(Interrupt Interrupt, InterruptAssignment assignment) final;
    };
}