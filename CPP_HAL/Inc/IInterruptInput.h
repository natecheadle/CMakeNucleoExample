#include <functional>

namespace CPP_HAL {
    class IInterruptInput
    {
    public:
        virtual ~IInterruptInput() = default;
        virtual bool Read() = 0;
        virtual void SetOnRiseFunc(std::function<void()> intFunc) = 0;
        virtual void SetOnFallFunc(std::function<void()> intFunc) = 0;
        virtual void ClearInterrupt() = 0;
    };
}