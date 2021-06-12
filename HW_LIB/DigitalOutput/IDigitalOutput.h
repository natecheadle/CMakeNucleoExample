namespace HW_LIB {
    class IDigitalOutput
    {
    public:
        virtual ~IDigitalOutput() = default;
        virtual void Write(bool level) = 0;
        virtual void Toggle() = 0;
    };
}