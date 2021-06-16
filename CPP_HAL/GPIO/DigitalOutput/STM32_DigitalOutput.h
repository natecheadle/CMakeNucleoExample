#pragma once

#include <cstdint>
#include <stm32f3xx_hal.h>

#include "IDigitalOutput.h"
#include "../Pins/DO_Pin.h"

namespace CPP_HAL{

    class STM32_DigitalOutput : public IDigitalOutput
    {
    public:
        STM32_DigitalOutput(DO_Pin pin);
        virtual ~STM32_DigitalOutput();

        void Write(bool level) final;
        void Toggle() final;

        Pin_ID GetPin() { return m_AssignedPin.GetID(); }
        DO_Pin::FREQUENCY GetFrequency() { return m_AssignedPin.GetFrequency(); }

    private:
        const DO_Pin m_AssignedPin;
    };
}