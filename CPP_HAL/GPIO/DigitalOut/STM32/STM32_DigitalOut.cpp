#include "STM32_DigitalOut.h"

#include <CPP_HAL.h>

namespace CPP_HAL{

    STM32_DigitalOut::STM32_DigitalOut(DO_Pin<STM32_Pin> pin) :
        m_AssignedPin(pin)

    {
        CPP_HAL::Initialize();

        GPIO_InitTypeDef GPIO_InitStruct = {0};

        GPIO_InitStruct.Pin = m_AssignedPin.GetLowLevelPin().GetHALPin();
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;

        GPIO_InitStruct.Speed = 
            m_AssignedPin.GetFrequency() == DO_Pin<STM32_Pin>::FREQUENCY::LOW ? GPIO_SPEED_FREQ_LOW :
            m_AssignedPin.GetFrequency() == DO_Pin<STM32_Pin>::FREQUENCY::MEDIUM ? GPIO_SPEED_FREQ_MEDIUM :
            m_AssignedPin.GetFrequency() == DO_Pin<STM32_Pin>::FREQUENCY::HIGH ? GPIO_SPEED_FREQ_HIGH :
            GPIO_SPEED_FREQ_LOW;
        
        HAL_GPIO_Init(m_AssignedPin.GetLowLevelPin().GetHALPort(), &GPIO_InitStruct);
        Write(false);
    }

    STM32_DigitalOut::~STM32_DigitalOut()
    {
        HAL_GPIO_DeInit(m_AssignedPin.GetLowLevelPin().GetHALPort(), m_AssignedPin.GetLowLevelPin().GetHALPin());
    }

    void STM32_DigitalOut::do_write(bool level)
    {
        HAL_GPIO_WritePin(m_AssignedPin.GetLowLevelPin().GetHALPort(), m_AssignedPin.GetLowLevelPin().GetHALPin(), level ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }

    void STM32_DigitalOut::do_toggle()
    {
        HAL_GPIO_TogglePin(m_AssignedPin.GetLowLevelPin().GetHALPort(), m_AssignedPin.GetLowLevelPin().GetHALPin());
    }

    bool STM32_DigitalOut::do_read()
    {
        return HAL_GPIO_ReadPin(m_AssignedPin.GetLowLevelPin().GetHALPort(), m_AssignedPin.GetLowLevelPin().GetHALPin()) == GPIO_PIN_SET;
    }
}