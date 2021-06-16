#pragma once

#include <tuple>
#include <array>

#include <stm32f3xx_hal.h>
#include "Pin_ID.h"

namespace CPP_HAL
{
    class Pin
    {
    public:
        Pin(Pin_ID id);
        virtual ~Pin() = default;

        Pin_ID GetID() const { return m_ID; }
        GPIO_TypeDef *GetHALPort() const { return m_Port; }
        uint32_t GetHALPin() const { return m_Pin; }
    private:
        enum class Port
        {
            A,
            B,
            C,
            D,
            F,
            SIZE
        };
        static std::array<bool, size_t(Port::SIZE)> s_ClockInitialized;
        static void InitGPIOClock(GPIO_TypeDef * GPIOPort);
        const Pin_ID m_ID;
        GPIO_TypeDef* m_Port;
        const uint32_t m_Pin;

        static constexpr std::tuple<GPIO_TypeDef *, uint32_t> PinLookup(Pin_ID id) noexcept
        {
            return 
            Pin_ID::PA_0 == id ? std::make_tuple(GPIOA, GPIO_PIN_0) :
            Pin_ID::PA_1 == id ? std::make_tuple(GPIOA, GPIO_PIN_1) :
            Pin_ID::PA_2 == id ? std::make_tuple(GPIOA, GPIO_PIN_2) :
            Pin_ID::PA_3 == id ? std::make_tuple(GPIOA, GPIO_PIN_3) :
            Pin_ID::PA_4 == id ? std::make_tuple(GPIOA, GPIO_PIN_4) :
            Pin_ID::PA_5 == id ? std::make_tuple(GPIOA, GPIO_PIN_5) :
            Pin_ID::PA_6 == id ? std::make_tuple(GPIOA, GPIO_PIN_6) :
            Pin_ID::PA_7 == id ? std::make_tuple(GPIOA, GPIO_PIN_7) :
            Pin_ID::PA_8 == id ? std::make_tuple(GPIOA, GPIO_PIN_8) :
            Pin_ID::PA_9 == id ? std::make_tuple(GPIOA, GPIO_PIN_9) :
            Pin_ID::PA_10 == id ? std::make_tuple(GPIOA, GPIO_PIN_10) :
            Pin_ID::PA_11 == id ? std::make_tuple(GPIOA, GPIO_PIN_11) :
            Pin_ID::PA_12 == id ? std::make_tuple(GPIOA, GPIO_PIN_12) :
            Pin_ID::PA_13 == id ? std::make_tuple(GPIOA, GPIO_PIN_13) :
            Pin_ID::PA_14 == id ? std::make_tuple(GPIOA, GPIO_PIN_14) :
            Pin_ID::PA_15 == id ? std::make_tuple(GPIOA, GPIO_PIN_15) :

            Pin_ID::PB_0 == id ? std::make_tuple(GPIOB, GPIO_PIN_0) :
            Pin_ID::PB_1 == id ? std::make_tuple(GPIOB, GPIO_PIN_1) :
            Pin_ID::PB_2 == id ? std::make_tuple(GPIOB, GPIO_PIN_2) :
            Pin_ID::PB_3 == id ? std::make_tuple(GPIOB, GPIO_PIN_3) :
            Pin_ID::PB_4 == id ? std::make_tuple(GPIOB, GPIO_PIN_4) :
            Pin_ID::PB_5 == id ? std::make_tuple(GPIOB, GPIO_PIN_5) :
            Pin_ID::PB_6 == id ? std::make_tuple(GPIOB, GPIO_PIN_6) :
            Pin_ID::PA_7 == id ? std::make_tuple(GPIOB, GPIO_PIN_7) :
            Pin_ID::PB_8 == id ? std::make_tuple(GPIOB, GPIO_PIN_8) :
            Pin_ID::PB_9 == id ? std::make_tuple(GPIOB, GPIO_PIN_9) :
            Pin_ID::PB_10 == id ? std::make_tuple(GPIOB, GPIO_PIN_10) :
            Pin_ID::PB_11 == id ? std::make_tuple(GPIOB, GPIO_PIN_11) :
            Pin_ID::PB_12 == id ? std::make_tuple(GPIOB, GPIO_PIN_12) :
            Pin_ID::PB_13 == id ? std::make_tuple(GPIOB, GPIO_PIN_13) :
            Pin_ID::PB_14 == id ? std::make_tuple(GPIOB, GPIO_PIN_14) :
            Pin_ID::PB_15 == id ? std::make_tuple(GPIOB, GPIO_PIN_15) :

            Pin_ID::PC_0 == id ? std::make_tuple(GPIOC, GPIO_PIN_0) :
            Pin_ID::PC_1 == id ? std::make_tuple(GPIOC, GPIO_PIN_1) :
            Pin_ID::PC_2 == id ? std::make_tuple(GPIOC, GPIO_PIN_2) :
            Pin_ID::PC_3 == id ? std::make_tuple(GPIOC, GPIO_PIN_3) :
            Pin_ID::PC_4 == id ? std::make_tuple(GPIOC, GPIO_PIN_4) :
            Pin_ID::PC_5 == id ? std::make_tuple(GPIOC, GPIO_PIN_5) :
            Pin_ID::PC_6 == id ? std::make_tuple(GPIOC, GPIO_PIN_6) :
            Pin_ID::PC_7 == id ? std::make_tuple(GPIOC, GPIO_PIN_7) :
            Pin_ID::PC_8 == id ? std::make_tuple(GPIOC, GPIO_PIN_8) :
            Pin_ID::PC_9 == id ? std::make_tuple(GPIOC, GPIO_PIN_9) :
            Pin_ID::PC_10 == id ? std::make_tuple(GPIOC, GPIO_PIN_10) :
            Pin_ID::PC_11 == id ? std::make_tuple(GPIOC, GPIO_PIN_11) :
            Pin_ID::PC_12 == id ? std::make_tuple(GPIOC, GPIO_PIN_12) :
            Pin_ID::PC_13 == id ? std::make_tuple(GPIOC, GPIO_PIN_13) :
            Pin_ID::PC_14 == id ? std::make_tuple(GPIOC, GPIO_PIN_14) :
            Pin_ID::PC_15 == id ? std::make_tuple(GPIOC, GPIO_PIN_15) : 
            
            std::make_tuple(nullptr, 0);
        }
    };
}