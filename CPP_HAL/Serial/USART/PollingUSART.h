#pragma once

#include <chrono>

namespace CPP_HAL{

    template<class Derived>
    class PollingUSART {
    public:
        enum class BaudRate {
            Baud_2400 = 2400,
            Baud_9600 = 9600,
            Baud_19200 = 19200,
            Baud_38400 = 38400,
            Baud_57600 = 57600,
            Baud_115200 = 115200,
            Baud_230400 = 230400,
            Baud_460800 = 460800,
            Baud_921600 = 921600
        };

        enum class WordLength {
            Bits_7,
            Bits_8,
            Bits_9
        };

        enum class StopBits {
            StopBits_0_5,
            StopBits_1,
            StopBits_1_5,
            StopBits_2
        };

        enum class Parity {
            None,
            Even,
            Odd
        };

        enum class Mode {
            TxOnly,
            RxOnly,
            TxAndRx
        };

        enum class FlowControlMode{
            None,
            RTS,
            CTS,
            RTS_And_CTS
        };

        enum class OverSampling{
            Sixteen,
            Eight
        };

        BaudRate GetBaudRate() const { return m_BaudRate; }
        WordLength GetWordLength() const { return m_WordLength; }
        StopBits GetStopBits() const { return m_StopBits; }
        Parity GetParity() const { return m_Parity; }
        Mode GetMode() const { return m_Mode; }
        FlowControlMode GetFlowControlMode() const { return m_FlowControlMode; }
        OverSampling GetOverSampling() const { return m_OverSampling; }

        bool SendBytes(const uint8_t* pData, size_t size, std::chrono::milliseconds timeout)
        {
            return static_cast<Derived*>(this)->do_sendBytes(pData, size, timeout);
        }
        bool ReceiveBytes(uint8_t* pData, size_t size, size_t& receivedBytes, std::chrono::milliseconds timeout)
        {
            return static_cast<Derived*>(this)->do_receiveBytes(pData, size, receivedBytes, timeout);
        }

    protected:
        PollingUSART(
                BaudRate baudRate,
                WordLength wordLength,
                StopBits stopBits,
                Parity parity,
                Mode mode,
                FlowControlMode flowControlMode,
                OverSampling overSampling ) :
            m_BaudRate(baudRate),
            m_WordLength(wordLength),
            m_StopBits(stopBits),
            m_Parity(parity),
            m_Mode(mode),
            m_FlowControlMode(flowControlMode),
            m_OverSampling(overSampling)
            {
            }

        virtual bool do_sendBytes(const uint8_t* pData, size_t size, std::chrono::milliseconds timeout) = 0;
        virtual bool do_receiveBytes(uint8_t* pData, size_t size, size_t& receivedBytes, std::chrono::milliseconds timeout) = 0;

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



