#include <functional>

namespace CPP_HAL {
    class IInterrupt
    {
    public:
        virtual ~IInterrupt() = default;
        virtual bool Read() = 0;

        virtual void AssignFunctor(std::function<void()> functor) = 0;
        virtual std::function<void()> GetFunctor() const = 0;
    };
}