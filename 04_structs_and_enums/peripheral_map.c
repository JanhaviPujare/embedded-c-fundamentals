#include "peripheral_map.h"
#include <stdio.h>

void GPIO_ConfigPin(GPIO_TypeDef *port, uint8_t pin, GPIO_Mode_t mode, GPIO_OType_t otype, GPIO_Speed_t speed, GPIO_PuPd_t pupd) {
    // Configure mode — 2 bits per pin
    port->MODER   &= ~(3U << (pin * 2));
    port->MODER   |=  (mode  << (pin * 2));
    // Configure output type — 1 bit per pin
    port->OTYPER  &= ~(1U << pin);
    port->OTYPER  |=  (otype << pin);
    // Configure speed — 2 bits per pin
    port->OSPEEDR &= ~(3U << (pin * 2));
    port->OSPEEDR |=  (speed << (pin * 2));
    // Configure pull up/down — 2 bits per pin
    port->PUPDR   &= ~(3U << (pin * 2));
    port->PUPDR   |=  (pupd  << (pin * 2));
}

void GPIO_WritePin(GPIO_TypeDef *port, uint8_t pin, GPIO_PinState_t state) {
    if(state == GPIO_PIN_HIGH) {
        port->ODR |=  (1U << pin);
    } else {
        port->ODR &= ~(1U << pin);
    }
}

GPIO_PinState_t GPIO_ReadPin(GPIO_TypeDef *port, uint8_t pin) {
    if(port->IDR & (1U << pin)) {
        return GPIO_PIN_HIGH;
    } else {
        return GPIO_PIN_LOW;
    }
}

void print_gpio_state(GPIO_TypeDef *port, char *name) {
    printf("\n--- %s Registers ---\n", name);
    printf("MODER:   0x%08X\n", port->MODER);
    printf("OTYPER:  0x%08X\n", port->OTYPER);
    printf("OSPEEDR: 0x%08X\n", port->OSPEEDR);
    printf("PUPDR:   0x%08X\n", port->PUPDR);
    printf("ODR:     0x%08X\n", port->ODR);
    printf("IDR:     0x%08X\n", port->IDR);
    printf("BSRR:    0x%08X\n", port->BSRR);
}