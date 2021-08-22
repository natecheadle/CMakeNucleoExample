
namespace CPP_HAL {
    enum class BaudRate {
        Baud_2400 = 2400,
        Baud_9600 = 9600,
        Baud_19200 = 19200,
        Baud_38400 = 38400,
        Baud_57600 = 57600,
        Baud_115200 = 115200,
        Baud_230400 = 230400,
        Baud_460800 = 460800,
        Baud_921600 = 921600
    };

    enum class WordLength {
        Bits_7,
        Bits_8,
        Bits_9
    };

    enum class StopBits {
        StopBits_0_5,
        StopBits_1,
        StopBits_1_5,
        StopBits_2
    };

    enum class Parity {
        None,
        Even,
        Odd
    };

    enum class Mode {
        TxOnly,
        RxOnly,
        TxAndRx
    };

    enum class FlowControlMode {
        None,
        RTS,
        CTS,
        RTS_And_CTS
    };

    enum class OverSampling {
        Sixteen,
        Eight
    };
}