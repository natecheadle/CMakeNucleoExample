#include <type_traits>

#include "../../inc/Interrupt.h"

namespace CPP_HAL {
    enum class DI_InterruptAssignment {
        RisingEdge,
        FallingEdge,
        RisingAndFallingEdge
    };

    template<class Derived>
    class DigitalIn {
    public:
        virtual ~DigitalIn() = default;

        bool Read() { return static_cast<Derived *>(this)->do_read(); }

        void AssignInterrupt(const Interrupt &Interrupt, DI_InterruptAssignment assignment) {
            static_cast<Derived *>(this)->do_assignInterrupt(Interrupt, assignment);
        }

    private:
        DigitalIn() = default;

        friend Derived;

        virtual bool do_read() = 0;

        virtual void do_assignInterrupt(const Interrupt &Interrupt, DI_InterruptAssignment assignment) = 0;
    };
}