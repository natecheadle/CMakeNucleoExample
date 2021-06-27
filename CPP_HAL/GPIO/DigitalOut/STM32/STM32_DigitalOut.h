#pragma once

#include <cstdint>
#include <stm32f3xx_hal.h>

#include "../DigitalOut.h"
#include "../../Pins/DO_Pin.h"

namespace CPP_HAL{

    class STM32_DigitalOut : public DigitalOut<STM32_DigitalOut>
    {
        friend DigitalOut;

    public:
        STM32_DigitalOut(DO_Pin pin);
        virtual ~STM32_DigitalOut();

        Pin_ID GetPin() { return m_AssignedPin.GetID(); }
        DO_Pin::FREQUENCY GetFrequency() { return m_AssignedPin.GetFrequency(); }

    private:
        virtual void do_write(bool level);
        virtual bool do_read();
        virtual void do_toggle();

        const DO_Pin m_AssignedPin;
    };
}