#pragma once

#include "IDigitalOutput.h"
#include <stm32f3xx_hal.h>

#include "../Pins.h"

namespace HW_LIB{

    class Embedded_DigitalOutput : public IDigitalOutput
    {
    public:
        Embedded_DigitalOutput(PIN pin, PULL pull = PULL::NONE, FREQUENCY freq = FREQUENCY::LOW);
        virtual ~Embedded_DigitalOutput();

        void Write(bool level) final;
        void Toggle() final;

        PIN GetPin() { return m_AssignedPin; }
        PULL GetPull() { return m_ConfiguredPull; }
        FREQUENCY GetFrequency() { return m_ConfiguredFrequency; }

    private:
        GPIO_TypeDef* GetHALPort(PIN pin);
        unsigned int GetHALPin(PIN pin);

        const PIN m_AssignedPin;
        const PULL m_ConfiguredPull;
        const FREQUENCY m_ConfiguredFrequency;

        const unsigned int m_HALPin;
        GPIO_TypeDef* const m_HALPort;
    };
}