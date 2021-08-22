namespace CPP_HAL {
    template<class Derived>
    class DigitalOut {
    public:
        virtual ~DigitalOut() = default;

        void Write(bool level) { static_cast<Derived *>(this)->do_write(level); }

        bool Read() { return static_cast<Derived *>(this)->do_read(); };

        void Toggle() { static_cast<Derived *>(this)->do_toggle(); }

    private:
        DigitalOut() = default;

        friend Derived;

        virtual void do_write(bool level) = 0;

        virtual bool do_read() = 0;

        virtual void do_toggle() = 0;
    };
}