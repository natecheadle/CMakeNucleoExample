namespace CPP_HAL {
    class IDigitalIn
    {
    public:
        virtual ~IDigitalIn() = default;
        virtual bool Read() = 0;
    };
}