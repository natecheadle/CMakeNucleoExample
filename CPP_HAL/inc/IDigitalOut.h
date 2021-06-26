namespace CPP_HAL {
    class IDigitalOut
    {
    public:
        virtual ~IDigitalOut() = default;
        virtual void Write(bool level) = 0;
        virtual bool Read() = 0;
        virtual void Toggle() = 0;
    };
}