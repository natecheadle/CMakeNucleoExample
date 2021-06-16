#include "Pin.h"

namespace CPP_HAL
{
    class DO_Pin : public Pin
    {
    public:
        enum class FREQUENCY
        {
            LOW,
            MEDIUM,
            HIGH
        };

        DO_Pin(Pin_ID pin, FREQUENCY freq = FREQUENCY::LOW);
        virtual ~DO_Pin() = default;

        FREQUENCY GetFrequency() const { return m_Frequency; }

    private:
        const FREQUENCY m_Frequency;
    };
}