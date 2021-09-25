#include "STM32_AsynchronousUSART.h"

namespace CPP_HAL {
    enum class InterruptID{
        TransmitDataRegisterEmpty = 0,
        ClearToSendFlag,
        TransmissionComplete,
        ReceivedDataReadyToBeRead,
        OverrunErrorDetected,
        IdleLineDetected,
        ParityError,
        BreakFlag,
        NoiseFlag,
        OverrunError,
        FramingError,
        InterruptID_Last
    };

    bool s_IsConstructed = false;
    UART_HandleTypeDef* s_HUART = nullptr;
    std::array<std::function<void()>, size_t(InterruptID::InterruptID_Last)> s_InterruptFunctors;

    STM32_AsynchronousUSART::STM32_AsynchronousUSART(
            DIO_Pin<STM32_Pin> rxPin,
            DIO_Pin<STM32_Pin> txPin,
            BaudRate baudRate,
            WordLength wordLength,
            StopBits stopBits,
            Parity parity,
            Mode mode,
            FlowControlMode flowControlMode,
            OverSampling overSampling) :
            AsynchronousUSART(baudRate, wordLength, stopBits, parity, mode, flowControlMode, overSampling),
            m_RxPin(rxPin),
            m_TxPin(txPin) {
        GPIO_InitTypeDef GPIO_InitStruct = populateGPIOStruct(m_TxPin);
        HAL_GPIO_Init(m_TxPin.GetLowLevelPin().GetHALPort(), &GPIO_InitStruct);

        GPIO_InitStruct = populateGPIOStruct(m_RxPin);
        HAL_GPIO_Init(m_RxPin.GetLowLevelPin().GetHALPort(), &GPIO_InitStruct);

        m_HUART = populateUARTStruct();

        if (HAL_UART_Init(&m_HUART) != HAL_OK) {
            //Error_Handler();
        }

        s_InterruptFunctors.at(size_t(InterruptID::TransmissionComplete)) = std::bind(&STM32_AsynchronousUSART::OnTransmissionComplete, this);

        if(m_HUART.Instance == USART2)
        {
            HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
            HAL_NVIC_EnableIRQ(USART2_IRQn);
        }
        else if(m_HUART.Instance == USART1)
        {
            HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
            HAL_NVIC_EnableIRQ(USART1_IRQn);
        }
        else if(m_HUART.Instance == USART3)
        {
            HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);
            HAL_NVIC_EnableIRQ(USART3_IRQn);
        }
        s_HUART = &m_HUART;
        s_IsConstructed = true;
    }

    STM32_AsynchronousUSART::~STM32_AsynchronousUSART()
    {
        s_IsConstructed = false;
        HAL_UART_Abort(&m_HUART);
    }


    void STM32_AsynchronousUSART::do_sendBytes(const uint8_t *pData, size_t size, const std::function<void()>& f_OnComplete) {
        const AsyncMsg* msg = allocateBytes(pData, size, f_OnComplete);
        HAL_UART_Transmit_IT(
                &m_HUART,
                const_cast<uint8_t*>(msg->Begin),
                static_cast<uint16_t>(msg->Size));
    }

    void STM32_AsynchronousUSART::do_receiveBytes(unsigned char *pData, size_t size, const std::function<void()>& f_OnComplete) {
        HAL_UART_Receive_IT(
                &m_HUART,
                pData,
                static_cast<uint16_t>(size));
    }

    GPIO_InitTypeDef STM32_AsynchronousUSART::populateGPIOStruct(const DIO_Pin<STM32_Pin> &pin) const {
        GPIO_InitTypeDef GPIO_InitStruct = {0};

        GPIO_InitStruct.Pin = pin.GetLowLevelPin().GetHALPin();
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull =
                pin.GetPull() == DIO_PULL::NoPull ? GPIO_NOPULL :
                pin.GetPull() == DIO_PULL::PullDown ? GPIO_PULLDOWN :
                pin.GetPull() == DIO_PULL::PullUp ? GPIO_PULLUP : GPIO_NOPULL;

        GPIO_InitStruct.Speed =
                pin.GetFrequency() == DIO_FREQUENCY::LOW ? GPIO_SPEED_FREQ_LOW :
                pin.GetFrequency() == DIO_FREQUENCY::MEDIUM ? GPIO_SPEED_FREQ_MEDIUM :
                pin.GetFrequency() == DIO_FREQUENCY::HIGH ? GPIO_SPEED_FREQ_HIGH :
                GPIO_SPEED_FREQ_LOW;

        return GPIO_InitStruct;
    }

    UART_HandleTypeDef STM32_AsynchronousUSART::populateUARTStruct() const {
        UART_HandleTypeDef huart{0};

        huart.Instance = GetUSARTInstance(m_RxPin.GetID(), m_TxPin.GetID());
        huart.Init.BaudRate = static_cast<uint32_t>(GetBaudRate());
        huart.Init.WordLength =
                GetWordLength() == WordLength::Bits_7 ? UART_WORDLENGTH_7B :
                GetWordLength() == WordLength::Bits_8 ? UART_WORDLENGTH_8B :
                UART_WORDLENGTH_9B;
        huart.Init.StopBits =
                GetStopBits() == StopBits::StopBits_0_5 ? UART_STOPBITS_0_5 :
                GetStopBits() == StopBits::StopBits_1 ? UART_STOPBITS_1 :
                GetStopBits() == StopBits::StopBits_1_5 ? UART_STOPBITS_1_5 :
                UART_STOPBITS_2;
        huart.Init.Parity =
                GetParity() == Parity::None ? UART_PARITY_NONE :
                GetParity() == Parity::Even ? UART_PARITY_EVEN :
                UART_PARITY_ODD;
        huart.Init.Mode =
                GetMode() == Mode::TxOnly ? UART_MODE_TX :
                GetMode() == Mode::RxOnly ? UART_MODE_RX :
                UART_MODE_TX_RX;
        huart.Init.HwFlowCtl =
                GetFlowControlMode() == FlowControlMode::None ? UART_HWCONTROL_NONE :
                GetFlowControlMode() == FlowControlMode::RTS ? UART_HWCONTROL_RTS :
                GetFlowControlMode() == FlowControlMode::CTS ? UART_HWCONTROL_CTS :
                UART_HWCONTROL_RTS_CTS;
        huart.Init.OverSampling =
                GetOverSampling() == OverSampling::Sixteen ? UART_OVERSAMPLING_16 :
                UART_OVERSAMPLING_8;
        huart.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
        huart.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

        return huart;
    }

    USART_TypeDef* STM32_AsynchronousUSART::GetUSARTInstance(Pin_ID rxPin, Pin_ID txPin) {
        switch (rxPin) {
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

    void STM32_AsynchronousUSART::OnTransmissionComplete()
    {
        const AsyncMsg* pPrev = getNextMsg();
        pPrev->f_OnComplete();
        popNextMsg();
        const AsyncMsg* pMsg = getNextMsg();
        if(pMsg)
        {
            HAL_UART_Transmit_IT(
                    &m_HUART,
                    const_cast<uint8_t*>(pMsg->Begin),
                    static_cast<uint16_t>(pMsg->Size));
        }
    }

    extern "C" void USART2_IRQHandler(void)
    {
        if(s_HUART)
            HAL_UART_IRQHandler(s_HUART);
    }

    extern "C" void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
        if(s_IsConstructed)
            s_InterruptFunctors.at(size_t(InterruptID::TransmissionComplete))();
    }
}


