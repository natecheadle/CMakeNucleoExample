#pragma once

#include "Serial/USART/PollingUSART.h"

#include <stm32f3xx_hal.h>
#include "GPIO/Pins/STM32_Pin.h"
#include "GPIO/Pins/DI_Pin.h"
#include "GPIO/Pins/DO_Pin.h"

namespace CPP_HAL{
    class STM32_PollingUSART : public PollingUSART<STM32_PollingUSART> {
        friend PollingUSART;
    public:
        STM32_PollingUSART(
                DI_Pin<STM32_Pin> rxPin,
                DO_Pin<STM32_Pin> txPin,
                BaudRate baudRate,
                WordLength wordLength,
                StopBits stopBits,
                Parity parity,
                Mode mode,
                FlowControlMode flowControlMode,
                OverSampling overSampling );

    protected:
        bool do_sendBytes(const uint8_t* pData, size_t size, std::chrono::milliseconds timeout);
        bool do_receiveBytes(uint8_t* pData, size_t size, size_t& receivedBytes, std::chrono::milliseconds timeout);

    private:
        void populateStruct();
        static USART_TypeDef* GetUSARTInstance(const DI_Pin<STM32_Pin>& rxPin, const DO_Pin<STM32_Pin>& txPin);

        UART_HandleTypeDef m_HUART;
        DI_Pin<STM32_Pin> m_RxPin;
        DO_Pin<STM32_Pin> m_TxPin;

    };
}
