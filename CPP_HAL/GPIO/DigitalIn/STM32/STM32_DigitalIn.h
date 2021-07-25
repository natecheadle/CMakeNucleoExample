#pragma once

#include <cstdint>
#include <array>
#include <functional>

#include <stm32f3xx_hal.h>

#include "../DigitalIn.h"
#include "../../Pins/DI_Pin.h"
#include "../../Pins/STM32_Pin.h"

namespace CPP_HAL{
    class STM32_DigitalIn : public DigitalIn<STM32_DigitalIn>
    {
        friend DigitalIn;
    public:
        STM32_DigitalIn(DI_Pin<STM32_Pin> pin);
        virtual ~STM32_DigitalIn() = default;

        const DI_Pin<STM32_Pin>& GetPin() const { return m_AssignedPin; }

    protected:
        virtual GPIO_InitTypeDef populateStruct() const;
        
    private:
        bool do_read() final;
        void do_assignInterrupt(const Interrupt& Interrupt, DI_InterruptAssignment assignment) final;

        const DI_Pin<STM32_Pin> m_AssignedPin;
        Interrupt m_Interrupt;
    };
}