#include "STM32_Pin.h"
namespace CPP_HAL
{
    std::array<bool, size_t(STM32_Pin::Port::SIZE)> STM32_Pin::s_ClockInitialized = {false};

    STM32_Pin::STM32_Pin(Pin_ID id) :
        LowLevelPin(id),
        m_Pin(std::get<1>(PinLookup(id))),
        m_Port(std::get<0>(PinLookup(id)))
    {
        InitGPIOClock(m_Port);
    }

    void STM32_Pin::InitGPIOClock(GPIO_TypeDef * GPIOPort)
    {
        if(GPIOPort == GPIOA && !s_ClockInitialized.at(size_t(Port::A)))
        {
            __HAL_RCC_GPIOA_CLK_ENABLE();
            s_ClockInitialized.at(size_t(Port::A)) = true;
        }
        else if(GPIOPort == GPIOB && !s_ClockInitialized.at(size_t(Port::B)))
        {
            __HAL_RCC_GPIOB_CLK_ENABLE();
            s_ClockInitialized.at(size_t(Port::B)) = true;
        }
        else if(GPIOPort == GPIOC && !s_ClockInitialized.at(size_t(Port::C)))
        {
            __HAL_RCC_GPIOC_CLK_ENABLE();
            s_ClockInitialized.at(size_t(Port::C)) = true;
        }
        else if(GPIOPort == GPIOD && !s_ClockInitialized.at(size_t(Port::D)))
        {
            __HAL_RCC_GPIOD_CLK_ENABLE();
            s_ClockInitialized.at(size_t(Port::D)) = true;
        }
        else if(GPIOPort == GPIOF && !s_ClockInitialized.at(size_t(Port::F)))
        {
            __HAL_RCC_GPIOF_CLK_ENABLE();
            s_ClockInitialized.at(size_t(Port::F)) = true;
        }
    }
}
