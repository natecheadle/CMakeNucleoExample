#include "../inc/application.h"

#include <stm32f3xx_ll_gpio.h>
#include <main.h>

extern "C" {

void setup() {
    // For future episodes ;)
}

void loop() {
    //LL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
    LL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
    //LL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);

    HAL_Delay(200U);
}

}
