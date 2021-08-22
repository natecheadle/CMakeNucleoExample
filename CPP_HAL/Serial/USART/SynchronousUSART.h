#pragma once

#include <chrono>
#include "USARTBase.h"

namespace CPP_HAL {

    template<class Derived>
    class SynchronousUSART : public USARTBase {
    public:
        bool SendBytes(const uint8_t *pData, size_t size, std::chrono::milliseconds timeout) {
            return static_cast<Derived *>(this)->do_sendBytes(pData, size, timeout);
        }

        bool ReceiveBytes(uint8_t *pData, size_t size, std::chrono::milliseconds timeout) {
            return static_cast<Derived *>(this)->do_receiveBytes(pData, size, timeout);
        }

    protected:
        SynchronousUSART(
                BaudRate baudRate,
                WordLength wordLength,
                StopBits stopBits,
                Parity parity,
                Mode mode,
                FlowControlMode flowControlMode,
                OverSampling overSampling) :
                USARTBase(baudRate, wordLength, stopBits, parity, mode, flowControlMode, overSampling) {
        }

        virtual bool do_sendBytes(const uint8_t *pData, size_t size, std::chrono::milliseconds timeout) = 0;

        virtual bool
        do_receiveBytes(uint8_t *pData, size_t size, std::chrono::milliseconds timeout) = 0;

    };
}



