#pragma once

#include "Pin_ID.h"

namespace CPP_HAL {
    class LowLevelPin {
    public:
        LowLevelPin(Pin_ID id) :
                m_ID(id) {
        }

    protected:
        Pin_ID GetPinID() const { return m_ID; }

    private:
        const Pin_ID m_ID;
    };
}
