#include "STM32_DigitalOutput.h"
#include "../STM32_GPIO_Setup.h"

namespace CPP_HAL{

    STM32_DigitalOutput::STM32_DigitalOutput(PIN pin, PULL pull, FREQUENCY freq) :
        m_AssignedPin(pin),
        m_ConfiguredPull(pull),
        m_ConfiguredFrequency(freq),
        m_HALPin(STM32_GPIO_Setup::GetHALPin(pin)),
        m_HALPort(STM32_GPIO_Setup::GetHALPort(pin))

    {
        STM32_GPIO_Setup::InitClock();
        GPIO_InitTypeDef GPIO_InitStruct = {0};

        GPIO_InitStruct.Pin = m_HALPin;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;

        switch(pull)
        {
        case PULL::NONE:
            GPIO_InitStruct.Pull = GPIO_NOPULL;
            break;
        case PULL::UP:
            GPIO_InitStruct.Pull = GPIO_PULLUP;
            break;
        case PULL::DOWN:
            GPIO_InitStruct.Pull = GPIO_PULLDOWN;
            break;
        }

        switch (freq)
        {
        case FREQUENCY::LOW:
            GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
            break;
        case FREQUENCY::MEDIUM:
            GPIO_InitStruct.Pull = GPIO_SPEED_FREQ_MEDIUM;
            break;
        case FREQUENCY::HIGH:
            GPIO_InitStruct.Pull = GPIO_SPEED_FREQ_HIGH;
            break;
        }
        
        HAL_GPIO_Init(m_HALPort, &GPIO_InitStruct);
        Write(false);
    }

    STM32_DigitalOutput::~STM32_DigitalOutput()
    {
        HAL_GPIO_DeInit(m_HALPort, m_HALPin);
    }

    void STM32_DigitalOutput::Write(bool level)
    {
        HAL_GPIO_WritePin(m_HALPort, m_HALPin, level ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }

    void STM32_DigitalOutput::Toggle()
    {
        HAL_GPIO_TogglePin(m_HALPort, m_HALPin);
    }
}