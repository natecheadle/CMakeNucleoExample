#pragma once

#include <cstdint>
#include <stm32f3xx_hal.h>

#include "../DigitalOut.h"
#include "../../Pins/DO_Pin.h"
#include "../../Pins/STM32_Pin.h"

namespace CPP_HAL{

    class STM32_DigitalOut : public DigitalOut<STM32_DigitalOut>
    {
        friend DigitalOut;

    public:
        STM32_DigitalOut(DO_Pin<STM32_Pin> pin);
        virtual ~STM32_DigitalOut();

        const DO_Pin<STM32_Pin>& GetPin() const { return m_AssignedPin; }

    private:
        virtual void do_write(bool level);
        virtual bool do_read();
        virtual void do_toggle();

        const DO_Pin<STM32_Pin> m_AssignedPin;
    };
}