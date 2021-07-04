#pragma once
#include <type_traits>

#include "LowLevelPin.h"

namespace CPP_HAL
{
    template<class PlatformPin>
    class Pin
    {
    public:
        Pin(Pin_ID id):
            m_ID(id),
            m_LowLevelPin(id)
        {
            static_assert(std::is_base_of<LowLevelPin, PlatformPin>::value, "PlatformPin must derive from LowLevelPin.");
        }
        virtual ~Pin() = default;

        Pin_ID GetID() const { return m_ID; }
        const PlatformPin& GetLowLevelPin() const { return m_LowLevelPin; }
    private:
        const Pin_ID m_ID;
        const PlatformPin m_LowLevelPin;
    };
}