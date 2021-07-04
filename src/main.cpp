#include "main.h"

#include <cstring>
#include <GPIO/DigitalOut/STM32/STM32_DigitalOut.h>
#include <GPIO/DigitalIn/STM32/STM32_DigitalIn.h>

using namespace CPP_HAL;

UART_HandleTypeDef huart2;

static void MX_USART2_UART_Init();
void RunInterrupt();

unsigned int SleepTime;
unsigned int Multiplier;

int main()
{
  STM32_DigitalOut LED2(DO_Pin<STM32_Pin>(Pin_ID::PA_5));
  STM32_DigitalIn BUTTON1(DI_Pin<STM32_Pin>(Pin_ID::PC_13));

  DigitalIn<STM32_DigitalIn> *pButton1 = static_cast<DigitalIn<STM32_DigitalIn>*>(&BUTTON1);
  DigitalOut<STM32_DigitalOut> *pLed2 = static_cast<DigitalOut<STM32_DigitalOut>*>(&LED2);

  Multiplier = 1;
  SleepTime = Multiplier * 200;
  CPP_HAL::Interrupt buttonInt(RunInterrupt);
  pButton1->AssignInterrupt(buttonInt, DI_InterruptAssignment::FallingEdge);
  MX_USART2_UART_Init();
  while (1)
  {
    /* USER CODE END WHILE */
    pLed2->Toggle();
    
    HAL_Delay(SleepTime);
    const char* _out = "LED2 Toggled\r\n";
    HAL_UART_Transmit(&huart2, (uint8_t *) _out, strlen(_out), 10);
  }
}

static void MX_USART2_UART_Init(void)
{
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 38400;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    //Error_Handler();
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

