//
// Created by Nathan Cheadle on 7/7/21.
//

#include "STM32_PollingUSART.h"

namespace CPP_HAL {
    STM32_PollingUSART::STM32_PollingUSART(
            DI_Pin<STM32_Pin> rxPin,
            DO_Pin<STM32_Pin> txPin,
            BaudRate baudRate,
            WordLength wordLength,
            StopBits stopBits,
            Parity parity,
            Mode mode,
            FlowControlMode flowControlMode,
            OverSampling overSampling) :
            PollingUSART(baudRate, wordLength, stopBits, parity, mode, flowControlMode, overSampling),
            m_RxPin(rxPin),
            m_TxPin(txPin) {
        populateStruct();
    }

    bool STM32_PollingUSART::do_sendBytes(const uint8_t* pData, size_t size, std::chrono::milliseconds timeout) {
        return HAL_UART_Transmit(&m_HUART, const_cast<uint8_t*>(pData), static_cast<uint16_t>(size),
                          static_cast<uint32_t>(timeout.count())) == HAL_OK;
    }

    bool STM32_PollingUSART::do_receiveBytes(unsigned char *pData, size_t size, size_t &receivedBytes,
                                             std::chrono::milliseconds timeout) {
        return HAL_UART_Receive(&m_HUART, pData, static_cast<uint16_t>(size),
                          static_cast<uint32_t>(timeout.count())) == HAL_OK;
    }

    void STM32_PollingUSART::populateStruct() {
        m_HUART.Instance = GetUSARTInstance(m_RxPin, m_TxPin);
        m_HUART.Init.BaudRate = static_cast<uint32_t>(GetBaudRate());
        m_HUART.Init.WordLength =
                GetWordLength() == WordLength::Bits_7 ? UART_WORDLENGTH_7B :
                GetWordLength() == WordLength::Bits_8 ? UART_WORDLENGTH_8B :
                UART_WORDLENGTH_9B;
        m_HUART.Init.StopBits =
                GetStopBits() == StopBits::StopBits_0_5 ? UART_STOPBITS_0_5 :
                GetStopBits() == StopBits::StopBits_1 ? UART_STOPBITS_1 :
                GetStopBits() == StopBits::StopBits_1_5 ? UART_STOPBITS_1_5 :
                UART_STOPBITS_2;
        m_HUART.Init.Parity =
                GetParity() == Parity::None ? UART_PARITY_NONE :
                GetParity() == Parity::Even ? UART_PARITY_EVEN :
                UART_PARITY_ODD;
        m_HUART.Init.Mode =
                GetMode() == Mode::TxOnly ? UART_MODE_TX :
                GetMode() == Mode::RxOnly ? UART_MODE_RX :
                UART_MODE_TX_RX;
        m_HUART.Init.HwFlowCtl =
                GetFlowControlMode() == FlowControlMode::None ? UART_HWCONTROL_NONE :
                GetFlowControlMode() == FlowControlMode::RTS ? UART_HWCONTROL_RTS :
                GetFlowControlMode() == FlowControlMode::CTS ? UART_HWCONTROL_CTS :
                UART_HWCONTROL_RTS_CTS;
        m_HUART.Init.OverSampling =
                GetOverSampling() == OverSampling::Sixteen ? UART_OVERSAMPLING_16 :
                UART_OVERSAMPLING_8;
        m_HUART.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
        m_HUART.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
        if (HAL_UART_Init(&m_HUART) != HAL_OK) {
            //Error_Handler();
        }
    }

    USART_TypeDef* STM32_PollingUSART::GetUSARTInstance(const DI_Pin<STM32_Pin> &rxPin, const DO_Pin<STM32_Pin> &txPin) {
        switch (rxPin.GetID()) {
            case Pin_ID::PA_3:
            case Pin_ID::PA_15:
            case Pin_ID::PB_4:
                return USART2;
            case Pin_ID::PA_10:
            case Pin_ID::PB_7:
            case Pin_ID::PC_5:
                return USART1;
            case Pin_ID::PB_8:
            case Pin_ID::PB_11:
            case Pin_ID::PC_11:
                return USART3;
        }
        return nullptr;
    }
}

