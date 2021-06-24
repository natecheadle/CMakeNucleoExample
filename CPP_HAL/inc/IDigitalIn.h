#include "Interrupt.h"

namespace CPP_HAL {
    class IDigitalIn
    {
    public:
        enum class InterruptAssignment
        {
            RisingEdge,
            FallingEdge,
            RisingAndFallingEdge
        };

        virtual ~IDigitalIn() = default;
        virtual bool Read() = 0;
        virtual void AssignInterrupt(Interrupt Interrupt, InterruptAssignment assignment) = 0;
    };
}