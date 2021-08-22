#include "STM32_DigitalIn.h"

#include <CPP_HAL.h>

namespace CPP_HAL {
    std::array<std::function<void()>, 15> s_InterruptFunctors;

    constexpr std::function<void()> &GetFunctor(uint16_t pin) noexcept {
        switch (pin) {
            case GPIO_PIN_0:
                return s_InterruptFunctors.at(0);
            case GPIO_PIN_1:
                return s_InterruptFunctors.at(1);
            case GPIO_PIN_2:
                return s_InterruptFunctors.at(2);
            case GPIO_PIN_3:
                return s_InterruptFunctors.at(3);
            case GPIO_PIN_4:
                return s_InterruptFunctors.at(4);
            case GPIO_PIN_5:
                return s_InterruptFunctors.at(5);
            case GPIO_PIN_6:
                return s_InterruptFunctors.at(6);
            case GPIO_PIN_7:
                return s_InterruptFunctors.at(7);
            case GPIO_PIN_8:
                return s_InterruptFunctors.at(8);
            case GPIO_PIN_9:
                return s_InterruptFunctors.at(9);
            case GPIO_PIN_10:
                return s_InterruptFunctors.at(10);
            case GPIO_PIN_11:
                return s_InterruptFunctors.at(11);
            case GPIO_PIN_12:
                return s_InterruptFunctors.at(12);
            case GPIO_PIN_13:
                return s_InterruptFunctors.at(13);
            case GPIO_PIN_14:
                return s_InterruptFunctors.at(14);
            case GPIO_PIN_15:
                return s_InterruptFunctors.at(15);
        }

        return s_InterruptFunctors.at(0);
    }

    void AssignFunctor(const DI_Pin<STM32_Pin> &pin, std::function<void()> functor) {
        switch (pin.GetLowLevelPin().GetHALPin()) {
            case GPIO_PIN_0:
                s_InterruptFunctors.at(0) = functor;
                break;
            case GPIO_PIN_1:
                s_InterruptFunctors.at(1) = functor;
                break;
            case GPIO_PIN_2:
                s_InterruptFunctors.at(2) = functor;
                break;
            case GPIO_PIN_3:
                s_InterruptFunctors.at(3) = functor;
                break;
            case GPIO_PIN_4:
                s_InterruptFunctors.at(4) = functor;
                break;
            case GPIO_PIN_5:
                s_InterruptFunctors.at(5) = functor;
                break;
            case GPIO_PIN_6:
                s_InterruptFunctors.at(6) = functor;
                break;
            case GPIO_PIN_7:
                s_InterruptFunctors.at(7) = functor;
                break;
            case GPIO_PIN_8:
                s_InterruptFunctors.at(8) = functor;
                break;
            case GPIO_PIN_9:
                s_InterruptFunctors.at(9) = functor;
                break;
            case GPIO_PIN_10:
                s_InterruptFunctors.at(10) = functor;
                break;
            case GPIO_PIN_11:
                s_InterruptFunctors.at(11) = functor;
                break;
            case GPIO_PIN_12:
                s_InterruptFunctors.at(12) = functor;
                break;
            case GPIO_PIN_13:
                s_InterruptFunctors.at(13) = functor;
                break;
            case GPIO_PIN_14:
                s_InterruptFunctors.at(14) = functor;
                break;
            case GPIO_PIN_15:
                s_InterruptFunctors.at(15) = functor;
                break;
        }
    };

    STM32_DigitalIn::STM32_DigitalIn(DI_Pin<STM32_Pin> pin) :
            m_AssignedPin(pin) {
        CPP_HAL::Initialize();

        GPIO_InitTypeDef GPIO_InitStruct = populateStruct();
        HAL_GPIO_Init(pin.GetLowLevelPin().GetHALPort(), &GPIO_InitStruct);
    }

    bool STM32_DigitalIn::do_read() {
        return HAL_GPIO_ReadPin(m_AssignedPin.GetLowLevelPin().GetHALPort(),
                                m_AssignedPin.GetLowLevelPin().GetHALPin()) == GPIO_PIN_SET;
    }

    void STM32_DigitalIn::do_assignInterrupt(const Interrupt &interrupt, DI_InterruptAssignment assignment) {
        m_Interrupt = interrupt;

        GPIO_InitTypeDef GPIO_InitStruct = populateStruct();
        GPIO_InitStruct.Mode =
                assignment == DI_InterruptAssignment::FallingEdge ? GPIO_MODE_IT_FALLING :
                assignment == DI_InterruptAssignment::RisingEdge ? GPIO_MODE_IT_RISING :
                GPIO_MODE_IT_RISING_FALLING;

        HAL_GPIO_Init(m_AssignedPin.GetLowLevelPin().GetHALPort(), &GPIO_InitStruct);
        AssignFunctor(m_AssignedPin, m_Interrupt.GetFunctor());
        switch (m_AssignedPin.GetLowLevelPin().GetHALPin()) {
            case GPIO_PIN_0:
                HAL_NVIC_EnableIRQ(EXTI0_IRQn);
                break;
            case GPIO_PIN_1:
                HAL_NVIC_EnableIRQ(EXTI1_IRQn);
                break;
            case GPIO_PIN_2:
                HAL_NVIC_EnableIRQ(EXTI2_TSC_IRQn);
                break;
            case GPIO_PIN_3:
                HAL_NVIC_EnableIRQ(EXTI3_IRQn);
                break;
            case GPIO_PIN_4:
                HAL_NVIC_EnableIRQ(EXTI4_IRQn);
                break;
            case GPIO_PIN_5:
            case GPIO_PIN_6:
            case GPIO_PIN_7:
            case GPIO_PIN_8:
            case GPIO_PIN_9:
                HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
                break;
            case GPIO_PIN_10:
            case GPIO_PIN_11:
            case GPIO_PIN_12:
            case GPIO_PIN_13:
            case GPIO_PIN_14:
            case GPIO_PIN_15:
                HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
                break;
        }
    }

    GPIO_InitTypeDef STM32_DigitalIn::populateStruct() const {
        GPIO_InitTypeDef GPIO_InitStruct = {0};

        GPIO_InitStruct.Pin = m_AssignedPin.GetLowLevelPin().GetHALPin();
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull =
                m_AssignedPin.GetPull() == DIO_PULL::NoPull ? GPIO_NOPULL :
                m_AssignedPin.GetPull() == DIO_PULL::PullDown ? GPIO_PULLDOWN :
                m_AssignedPin.GetPull() == DIO_PULL::PullUp ? GPIO_PULLUP : GPIO_NOPULL;

        return GPIO_InitStruct;
    }

    extern "C" void EXTI0_IRQHandler() {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0);
        GetFunctor(GPIO_PIN_0)();
    }

    extern "C" void EXTI1_IRQHandler() {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_1);
        GetFunctor(GPIO_PIN_1)();
    }

    extern "C" void EXTI2_TSC_IRQHandler() {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_2);
        GetFunctor(GPIO_PIN_2)();
    }

    extern "C" void EXTI3_IRQHandler() {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_3);
        GetFunctor(GPIO_PIN_3)();
    }

    extern "C" void EXTI4_IRQHandler() {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_4);
        GetFunctor(GPIO_PIN_4)();
    }

    extern "C" void EXTI9_5_IRQHandler() {
        HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
        HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);
        HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);
        HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_8);
        HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_8);
        HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_9);
    }

    extern "C" void EXTI15_10_IRQHandler() {
        HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);
        HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);
        HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);
        HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
        HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_14);
        HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_15);
    }

    extern "C" void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
        GetFunctor(GPIO_Pin)();
    }
}