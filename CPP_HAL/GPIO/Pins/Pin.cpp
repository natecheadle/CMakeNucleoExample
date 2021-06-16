#include "Pin.h"

namespace CPP_HAL 
{
    std::array<bool, size_t(Pin::Port::SIZE)> Pin::s_ClockInitialized = {false};

    Pin::Pin(Pin_ID id) :
        m_ID(id),
        m_Pin(std::get<1>(PinLookup(id))),
        m_Port(std::get<0>(PinLookup(id)))
    {
        Pin::InitGPIOClock(m_Port);
    }

    void Pin::InitGPIOClock(GPIO_TypeDef * GPIOPort)
    {
        if(GPIOPort == GPIOA && !s_ClockInitialized.at(size_t(Port::A)))
        {
            __HAL_RCC_GPIOA_CLK_ENABLE();
            s_ClockInitialized.at(size_t(Port::A)) = true;
        }
        else if(GPIOPort == GPIOB && !s_ClockInitialized.at(size_t(Port::B)))
        {
            __HAL_RCC_GPIOA_CLK_ENABLE();
            s_ClockInitialized.at(size_t(Port::B)) = true;
        }
        else if(GPIOPort == GPIOC && !s_ClockInitialized.at(size_t(Port::C)))
        {
            __HAL_RCC_GPIOA_CLK_ENABLE();
            s_ClockInitialized.at(size_t(Port::C)) = true;
        }
        else if(GPIOPort == GPIOD && !s_ClockInitialized.at(size_t(Port::D)))
        {
            __HAL_RCC_GPIOA_CLK_ENABLE();
            s_ClockInitialized.at(size_t(Port::D)) = true;
        }
        else if(GPIOPort == GPIOF && !s_ClockInitialized.at(size_t(Port::F)))
        {
            __HAL_RCC_GPIOA_CLK_ENABLE();
            s_ClockInitialized.at(size_t(Port::F)) = true;
        }
    }
}