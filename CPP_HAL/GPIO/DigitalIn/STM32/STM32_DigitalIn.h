#pragma once

#include <cstdint>
#include <array>
#include <functional>

#include <stm32f3xx_hal.h>

#include "../DigitalIn.h"
#include "../../Pins/DI_Pin.h"

namespace CPP_HAL{
    class STM32_DigitalIn : public DigitalIn<STM32_DigitalIn>
    {
        friend DigitalIn;
    public:
        STM32_DigitalIn(DI_Pin pin);
        virtual ~STM32_DigitalIn() = default;

        DI_Pin GetPin() const { return m_AssignedPin; }

    protected:
        GPIO_InitTypeDef populateStruct();
        
    private:
        bool do_read() final;
        void do_assignInterrupt(const Interrupt& Interrupt, DI_InterruptAssignment assignment) final;

        const DI_Pin m_AssignedPin;
        Interrupt m_Interrupt;
    };
}