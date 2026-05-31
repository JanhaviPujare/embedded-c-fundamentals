#include "peripheral_map.h"
#include <stdio.h>


GPIO_TypeDef GPIOA = {0, 0, 0, 0, 0, 0, 0};
GPIO_TypeDef GPIOB = {0, 0, 0, 0, 0, 0, 0};
RCC_TypeDef  RCC   = {0, 0, 0};

int main(void) {

    printf("===== Peripheral Register Map Simulator =====\n");
    printf("STM32F4 GPIO and RCC Register Simulation\n\n");

   
    printf("-- Step 1: Enable Clocks --\n");
    RCC.AHB1ENR |= (1U << 0);  // bit 0 = GPIOA clock enable
    RCC.AHB1ENR |= (1U << 1);  // bit 1 = GPIOB clock enable
    printf("RCC AHB1ENR: 0x%08X\n", RCC.AHB1ENR);
    printf("GPIOA clock: %s\n",
           (RCC.AHB1ENR & (1U << 0)) ? "ENABLED" : "DISABLED");
    printf("GPIOB clock: %s\n",
           (RCC.AHB1ENR & (1U << 1)) ? "ENABLED" : "DISABLED");

    
    printf("\n-- Step 2: Configure PA5 as OUTPUT (LED) --\n");
    GPIO_ConfigPin(&GPIOA, 5,
                   GPIO_MODE_OUTPUT,
                   GPIO_OTYPE_PUSHPULL,
                   GPIO_SPEED_LOW,
                   GPIO_PUPD_NOPULL);
    print_gpio_state(&GPIOA, "GPIOA after PA5 config");

   
    printf("\n-- Step 3: Configure PB13 as INPUT (button) --\n");
    GPIO_ConfigPin(&GPIOB, 13,
                   GPIO_MODE_INPUT,
                   GPIO_OTYPE_PUSHPULL,
                   GPIO_SPEED_LOW,
                   GPIO_PUPD_PULLUP);
    print_gpio_state(&GPIOB, "GPIOB after PB13 config");

    
    printf("\n-- Step 4: LED Control --\n");
    GPIO_WritePin(&GPIOA, 5, GPIO_PIN_HIGH);
    printf("LED ON  --> ODR: 0x%08X\n", GPIOA.ODR);

    GPIO_WritePin(&GPIOA, 5, GPIO_PIN_LOW);
    printf("LED OFF --> ODR: 0x%08X\n", GPIOA.ODR);

    GPIO_WritePin(&GPIOA, 5, GPIO_PIN_HIGH);
    printf("LED ON  --> ODR: 0x%08X\n", GPIOA.ODR);

    
    printf("\n-- Step 5: Button Read --\n");

    // Simulate button NOT pressed
    GPIOB.IDR &= ~(1U << 13);
    printf("Button state (not pressed): %s\n",
           GPIO_ReadPin(&GPIOB, 13) == GPIO_PIN_HIGH ? "HIGH" : "LOW");

    // Simulate button pressed
    GPIOB.IDR |= (1U << 13);
    printf("Button state (pressed):     %s\n",
           GPIO_ReadPin(&GPIOB, 13) == GPIO_PIN_HIGH ? "HIGH" : "LOW");

   
    printf("\n-- Step 6: Final Register State --\n");
    print_gpio_state(&GPIOA, "GPIOA final");
    print_gpio_state(&GPIOB, "GPIOB final");

    return 0;
}