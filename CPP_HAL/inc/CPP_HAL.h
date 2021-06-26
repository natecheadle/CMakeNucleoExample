namespace CPP_HAL {
    class CPP_HAL
    {
        static bool IsInitialized;
        static void SystemClock_Config();
        static void ErrorHandler();
    public:
        static void Initialize();
        
    };
};