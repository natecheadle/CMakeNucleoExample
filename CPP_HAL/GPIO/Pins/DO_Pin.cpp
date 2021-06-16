#include "DO_Pin.h"

namespace CPP_HAL
{
    DO_Pin::DO_Pin(Pin_ID pin, FREQUENCY freq) :
        Pin(pin),
        m_Frequency(freq)
    {
        
    }

}