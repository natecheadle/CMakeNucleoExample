#pragma once

#include "Pin.h"
#include "DIO_FREQUENCY.h"

namespace CPP_HAL {
    template<class PlatformPin>
    class DO_Pin : public Pin<PlatformPin> {
    public:
        DO_Pin(Pin_ID pin, DIO_FREQUENCY freq = DIO_FREQUENCY::LOW) :
                Pin<PlatformPin>(pin),
                m_Frequency(freq) {
        }

        virtual ~DO_Pin() = default;

        DIO_FREQUENCY GetFrequency() const { return m_Frequency; }

    private:
        const DIO_FREQUENCY m_Frequency;
    };
}