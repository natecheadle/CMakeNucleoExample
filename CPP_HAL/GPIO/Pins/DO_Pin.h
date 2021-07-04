#include "Pin.h"

namespace CPP_HAL
{
    template<class PlatformPin>
    class DO_Pin : public Pin<PlatformPin>
    {
    public:
        enum class FREQUENCY
        {
            LOW,
            MEDIUM,
            HIGH
        };

        DO_Pin(Pin_ID pin, FREQUENCY freq = FREQUENCY::LOW) :
            Pin<PlatformPin>(pin),
            m_Frequency(freq)
        {
        }
        virtual ~DO_Pin() = default;

        FREQUENCY GetFrequency() const { return m_Frequency; }

    private:
        const FREQUENCY m_Frequency;
    };
}