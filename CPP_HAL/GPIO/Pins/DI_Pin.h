#pragma once

#include "Pin.h"
#include "DIO_PULL.h"

namespace CPP_HAL {
    template<class PlatformPin>
    class DI_Pin : public Pin<PlatformPin> {
    public:


        DI_Pin(Pin_ID pin, DIO_PULL pull = DIO_PULL::NoPull) :
                Pin<PlatformPin>(pin),
                m_Pull(pull) {

        }

        virtual ~DI_Pin() = default;

        DIO_PULL GetPull() const { return m_Pull; }

    private:
        const DIO_PULL m_Pull;
    };
}