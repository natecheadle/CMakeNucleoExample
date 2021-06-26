#include <functional>

namespace CPP_HAL {
    class Interrupt
    {
    public:
        Interrupt() { }
        Interrupt(std::function<void()> functor) :
            m_Functor(functor)
        {

        }
        ~Interrupt() = default;

        virtual std::function<void()> GetFunctor() const { return m_Functor; }

    private:
        std::function<void()> m_Functor;
    };
}