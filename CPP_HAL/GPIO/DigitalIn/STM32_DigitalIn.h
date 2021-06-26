#pragma once

#include <cstdint>
#include <array>
#include <functional>

#include <stm32f3xx_hal.h>

#include "IDigitalIn.h"
#include "../Pins/DI_Pin.h"

namespace CPP_HAL{
    class STM32_DigitalIn : public IDigitalIn 
    {
    public:
        STM32_DigitalIn(DI_Pin pin);
        virtual ~STM32_DigitalIn() = default;
        bool Read() final;
        void AssignInterrupt(Interrupt interrupt, InterruptAssignment assignment) final;

        DI_Pin GetPin() const { return m_AssignedPin; }

    protected:
        GPIO_InitTypeDef populateStruct();
        
    private:
        const DI_Pin m_AssignedPin;
        Interrupt m_Interrupt;
    };
}