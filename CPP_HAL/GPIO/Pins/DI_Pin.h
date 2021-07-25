#pragma once
#include "Pin.h"

namespace CPP_HAL
{
    template<class PlatformPin>
    class DI_Pin : public Pin<PlatformPin>
    {
    public:
        enum class Pull
        {
            PullUp,
            PullDown,
            NoPull
        };

        DI_Pin(Pin_ID pin, Pull pull = Pull::NoPull) :
            Pin<PlatformPin>(pin),
            m_Pull(pull)
        {
            
        }
        virtual ~DI_Pin() = default;

        Pull GetPull() const { return m_Pull; }

    private:
        const Pull m_Pull;
    };
}