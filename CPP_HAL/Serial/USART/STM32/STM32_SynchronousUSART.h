#pragma once

#include "Serial/USART/SynchronousUSART.h"

#include <stm32f3xx_hal.h>
#include "GPIO/Pins/DIO_Pin.h"
#include "GPIO/Pins/STM32_Pin.h"

namespace CPP_HAL {

    class STM32_SynchronousUSART : public SynchronousUSART<STM32_SynchronousUSART> {
        friend SynchronousUSART;
    public:
        STM32_SynchronousUSART(
                DIO_Pin<STM32_Pin> rxPin,
                DIO_Pin<STM32_Pin> txPin,
                BaudRate baudRate,
                WordLength wordLength,
                StopBits stopBits,
                Parity parity,
                Mode mode,
                FlowControlMode flowControlMode,
                OverSampling overSampling);

    protected:
        virtual GPIO_InitTypeDef populateGPIOStruct(const DIO_Pin<STM32_Pin> &pin) const;

        virtual UART_HandleTypeDef populateUARTStruct() const;

        bool do_sendBytes(const uint8_t *pData, size_t size, std::chrono::milliseconds timeout) final;

        bool do_receiveBytes(uint8_t *pData, size_t size, std::chrono::milliseconds timeout) final;

    private:
        static USART_TypeDef *GetUSARTInstance(Pin_ID rxPin, Pin_ID txPin);

        UART_HandleTypeDef m_HUART;
        const DIO_Pin<STM32_Pin> m_RxPin;
        const DIO_Pin<STM32_Pin> m_TxPin;

    };
}
