#pragma once

#include "USARTBase.h"
#include <Container/StaticQueue.hpp>
#include <chrono>
#include <functional>

namespace CPP_HAL {
    template<class Derived>
    class AsynchronousUSART : public USARTBase{
    protected:
        struct AsyncMsg{
            AsyncMsg() :
            Begin(nullptr),
            Size(0) {}

            AsyncMsg(const uint8_t* begin, const size_t size, const std::function<void()>& f_onComplete) :
            Begin(begin),
            Size(size),
            f_OnComplete(f_onComplete) {}

            const uint8_t* Begin;
            size_t Size;
            std::function<void()> f_OnComplete;
        };

    private:
        Shared::lib::StaticQueue<uint8_t, 1024> m_SendBuffer;
        Shared::lib::StaticQueue<AsyncMsg, 24> m_MsgBuffer;

    public:
        void SendBytes(const uint8_t *pData, size_t size, const std::function<void()>& f_OnComplete) {
            static_cast<Derived *>(this)->do_sendBytes(pData, size, f_OnComplete);
        }

        void ReceiveBytes(uint8_t *pData, size_t size, const std::function<void()>& f_OnComplete) {
            static_cast<Derived *>(this)->do_receiveBytes(pData, size, f_OnComplete);
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
        const AsyncMsg* getNextMsg()
        {
            return m_MsgBuffer.Size() ?
                m_MsgBuffer.Front() :
                nullptr;
        }

        void popNextMsg()
        {
            if(m_MsgBuffer.Size())
            {
                const AsyncMsg* pNxt = m_MsgBuffer.Front();
                for(size_t i = 0; i < pNxt->Size; ++i)
                    m_SendBuffer.Pop();

                m_MsgBuffer.Pop();
            }


        }


        const AsyncMsg* allocateBytes(const uint8_t *pData, size_t size, const std::function<void()>& f_OnComplete)
        {
            const AsyncMsg* returnVal = m_MsgBuffer.Back();
            for(size_t i = 0; i< size; ++i)
            {
                m_SendBuffer.Push(pData[i]);

                if(i == 0)
                    m_MsgBuffer.Push(AsyncMsg(m_SendBuffer.Back(), size, f_OnComplete));
            }

            return returnVal;
        }

        bool bytesToSend() { return !m_SendBuffer.Empty(); }

        virtual void do_sendBytes(const uint8_t *pData, size_t size, const std::function<void()>& f_OnComplete) = 0;

        virtual void do_receiveBytes(uint8_t *pData, size_t size, const std::function<void()>& f_OnComplete) = 0;

    };
}
