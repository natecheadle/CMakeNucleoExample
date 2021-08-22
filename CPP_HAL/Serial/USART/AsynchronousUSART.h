#pragma once

#include "USARTBase.h"
#include <Container/StaticQueue.hpp>
#include <chrono>
#include <functional>

namespace CPP_HAL {
    struct AsyncTransfer{
        AsyncTransfer() :
            Begin(nullptr),
            End(nullptr),
            IsComplete(false)
            {}

        AsyncTransfer(const uint8_t* begin, const uint8_t* end, bool isComplete) :
            Begin(nullptr),
            End(nullptr),
            IsComplete(false)
            {}

        const uint8_t* Begin;
        const uint8_t* End;
        bool IsComplete;
    };

    template<class Derived>
    class AsynchronousUSART : public USARTBase{
        Shared::lib::StaticQueue<uint8_t, 1024> m_SendBuffer;
        Shared::lib::StaticQueue<AsyncTransfer, 16> m_SendMessageQueue;

    public:
        bool SendBytes(const uint8_t *pData, size_t size, std::chrono::milliseconds timeout, std::function<void()> f_OnComplete) {
            return static_cast<Derived *>(this)->do_sendBytes(pData, size, timeout);
        }

        void ReceiveBytes(uint8_t *pData, size_t size, std::chrono::milliseconds timeout, std::function<void()> f_OnComplete) {
            return static_cast<Derived *>(this)->do_receiveBytes(pData, size, timeout);
        }

    protected:
        AsynchronousUSART(
                BaudRate baudRate,
                WordLength wordLength,
                StopBits stopBits,
                Parity parity,
                Mode mode,
                FlowControlMode flowControlMode,
                OverSampling overSampling) :
                USARTBase(baudRate, wordLength, stopBits, parity, mode, flowControlMode, overSampling){
        }

        const AsyncTransfer* allocateBytes(const uint8_t *pData, size_t size, std::function<void()> f_OnComplete)
        {
            if(m_SendMessageQueue.Full())
                return nullptr;

            AsyncTransfer nextMsg;
            nextMsg.Begin = m_SendBuffer.Back();
            for(size_t i; i< size; ++i)
            {
                m_SendBuffer.Push(pData[i]);
            }
            nextMsg.End = m_SendBuffer.Back();

            m_SendMessageQueue.Push(nextMsg);

            return m_SendMessageQueue.Back();
        }

        bool bytesToSend() { return !m_SendBuffer.Empty(); }

        uint8_t getNextByte()
        {
            const uint8_t* nextByte = m_SendBuffer.Front();
            AsyncTransfer* nextTransfer = m_SendMessageQueue.Front();

            uint8_t rtrnVal = *nextByte;
            m_SendBuffer.Pop();
            nextTransfer->IsComplete = true;
            return rtrnVal;
        }


        virtual void do_sendBytes(const uint8_t *pData, size_t size, std::chrono::milliseconds timeout) = 0;

        virtual void do_receiveBytes(uint8_t *pData, size_t size, std::chrono::milliseconds timeout) = 0;

    };
}
