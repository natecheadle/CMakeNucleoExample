#pragma once

#include <cstdint>
#include <stm32f3xx_hal.h>

#include "IDigitalOutput.h"
#include "Pins.h"

namespace CPP_HAL{

    class STM32_DigitalOutput : public IDigitalOutput
    {
    public:
        STM32_DigitalOutput(PIN pin, PULL pull = PULL::NONE, FREQUENCY freq = FREQUENCY::LOW);
        virtual ~STM32_DigitalOutput();

        void Write(bool level) final;
        void Toggle() final;

        PIN GetPin() { return m_AssignedPin; }
        PULL GetPull() { return m_ConfiguredPull; }
        FREQUENCY GetFrequency() { return m_ConfiguredFrequency; }

    private:
        const PIN m_AssignedPin;
        const PULL m_ConfiguredPull;
        const FREQUENCY m_ConfiguredFrequency;

        const uint32_t m_HALPin;
        GPIO_TypeDef* const m_HALPort;
    };
}