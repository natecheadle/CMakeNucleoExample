#include "main.h"

#include <cstring>
#include <GPIO/DigitalOut/STM32/STM32_DigitalOut.h>
#include <GPIO/DigitalIn/STM32/STM32_DigitalIn.h>
#include <Serial/USART/STM32/STM32_PollingUSART.h>

using namespace CPP_HAL;

void RunInterrupt();

unsigned int SleepTime;
unsigned int Multiplier;

int main()
{
  STM32_DigitalOut LED2(DO_Pin<STM32_Pin>(Pin_ID::PA_5));
  STM32_DigitalIn BUTTON1(DI_Pin<STM32_Pin>(Pin_ID::PC_13));
  STM32_PollingUSART Serial2(
          DIO_Pin<STM32_Pin>(Pin_ID::PA_3),
          DIO_Pin<STM32_Pin>(Pin_ID::PA_2),
          PollingUSART<STM32_PollingUSART>::BaudRate::Baud_38400,
          PollingUSART<STM32_PollingUSART>::WordLength::Bits_8,
          PollingUSART<STM32_PollingUSART>::StopBits::StopBits_1,
          PollingUSART<STM32_PollingUSART>::Parity::None,
          PollingUSART<STM32_PollingUSART>::Mode::TxAndRx,
          PollingUSART<STM32_PollingUSART>::FlowControlMode::None,
          PollingUSART<STM32_PollingUSART>::OverSampling::Sixteen);

  DigitalIn<STM32_DigitalIn> *pButton1 = static_cast<DigitalIn<STM32_DigitalIn>*>(&BUTTON1);
  DigitalOut<STM32_DigitalOut> *pLed2 = static_cast<DigitalOut<STM32_DigitalOut>*>(&LED2);

  Multiplier = 1;
  SleepTime = Multiplier * 200;
  CPP_HAL::Interrupt buttonInt(RunInterrupt);
  pButton1->AssignInterrupt(buttonInt, DI_InterruptAssignment::FallingEdge);
  while (1)
  {
    /* USER CODE END WHILE */
    pLed2->Toggle();
    
    HAL_Delay(SleepTime);
    const char* _out = "LED2 Toggled\r\n";
    Serial2.SendBytes(
            reinterpret_cast<const uint8_t*>(_out),
            strlen(_out),
            std::chrono::milliseconds(10));
  }
}

void RunInterrupt()
{
  Multiplier = ++Multiplier % 5;
  if(Multiplier == 0)
    Multiplier++;
  SleepTime = Multiplier * 200;
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

