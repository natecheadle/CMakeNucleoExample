#pragma once
#include "Pin.h"
#include "DIO_PULL.h"
#include "DIO_FREQUENCY.h"

namespace CPP_HAL
{
    template<class PlatformPin>
    class DIO_Pin : public Pin<PlatformPin>
    {
    public:
        DIO_Pin(Pin_ID pin, DIO_PULL pull = DIO_PULL::NoPull, DIO_FREQUENCY freq = DIO_FREQUENCY::LOW) :
            Pin<PlatformPin>(pin),
            m_Pull(pull),
            m_Frequency(freq)
        {

        }
        virtual ~DIO_Pin() = default;

        DIO_PULL GetPull() const { return m_Pull; }
        DIO_FREQUENCY GetFrequency() const { return m_Frequency; }

    private:
        const DIO_PULL m_Pull;
        const DIO_FREQUENCY m_Frequency;
    };
}