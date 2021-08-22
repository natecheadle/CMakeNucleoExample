#pragma once

#include "USART_Enums.h"

namespace CPP_HAL {

    class USARTBase {
    public:
        BaudRate GetBaudRate() const { return m_BaudRate; }

        WordLength GetWordLength() const { return m_WordLength; }

        StopBits GetStopBits() const { return m_StopBits; }

        Parity GetParity() const { return m_Parity; }

        Mode GetMode() const { return m_Mode; }

        FlowControlMode GetFlowControlMode() const { return m_FlowControlMode; }

        OverSampling GetOverSampling() const { return m_OverSampling; }

    protected:
        USARTBase(
                BaudRate baudRate,
                WordLength wordLength,
                StopBits stopBits,
                Parity parity,
                Mode mode,
                FlowControlMode flowControlMode,
                OverSampling overSampling) :
                m_BaudRate(baudRate),
                m_WordLength(wordLength),
                m_StopBits(stopBits),
                m_Parity(parity),
                m_Mode(mode),
                m_FlowControlMode(flowControlMode),
                m_OverSampling(overSampling) {
        }

    private:
        const BaudRate m_BaudRate;
        const WordLength m_WordLength;
        const StopBits m_StopBits;
        const Parity m_Parity;
        const Mode m_Mode;
        const FlowControlMode m_FlowControlMode;
        const OverSampling m_OverSampling;
    };
}



