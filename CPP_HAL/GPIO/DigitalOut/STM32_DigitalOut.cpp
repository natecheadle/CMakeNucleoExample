#include "STM32_DigitalOut.h"

namespace CPP_HAL{

    STM32_DigitalOut::STM32_DigitalOut(DO_Pin pin) :
        m_AssignedPin(pin)

    {
        GPIO_InitTypeDef GPIO_InitStruct = {0};

        GPIO_InitStruct.Pin = m_AssignedPin.GetHALPin();
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;

        GPIO_InitStruct.Speed = 
            GetFrequency() == DO_Pin::FREQUENCY::LOW ? GPIO_SPEED_FREQ_LOW :
            GetFrequency() == DO_Pin::FREQUENCY::MEDIUM ? GPIO_SPEED_FREQ_MEDIUM :
            GetFrequency() == DO_Pin::FREQUENCY::HIGH ? GPIO_SPEED_FREQ_HIGH :
            GPIO_SPEED_FREQ_LOW;
        
        HAL_GPIO_Init(m_AssignedPin.GetHALPort(), &GPIO_InitStruct);
        Write(false);
    }

    STM32_DigitalOut::~STM32_DigitalOut()
    {
        HAL_GPIO_DeInit(m_AssignedPin.GetHALPort(), m_AssignedPin.GetHALPin());
    }

    void STM32_DigitalOut::Write(bool level)
    {
        HAL_GPIO_WritePin(m_AssignedPin.GetHALPort(), m_AssignedPin.GetHALPin(), level ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }

    void STM32_DigitalOut::Toggle()
    {
        HAL_GPIO_TogglePin(m_AssignedPin.GetHALPort(), m_AssignedPin.GetHALPin());
    }
}