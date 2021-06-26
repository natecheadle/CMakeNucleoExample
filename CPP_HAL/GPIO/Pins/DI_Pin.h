#include "Pin.h"

namespace CPP_HAL
{
    class DI_Pin : public Pin
    {
    public:
        enum class Pull
        {
            PullUp,
            PullDown,
            NoPull
        };

        DI_Pin(Pin_ID pin, Pull pull = Pull::NoPull) :
            Pin(pin),
            m_Pull(pull)
        {
            
        }
        virtual ~DI_Pin() = default;

        Pull GetPull() const { return m_Pull; }

    private:
        const Pull m_Pull;
    };
}