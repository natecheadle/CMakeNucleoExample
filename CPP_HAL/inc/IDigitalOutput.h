namespace CPP_HAL {
    class IDigitalOutput
    {
    public:
        virtual ~IDigitalOutput() = default;
        virtual void Write(bool level) = 0;
        virtual void Toggle() = 0;
    };
}