#ifndef PERIPHERAL_MAP_H
#define PERIPHERAL_MAP_H

#include <stdint.h>

// GPIO register struct — mirrors real STM32 GPIO peripheral
typedef struct {
    uint32_t MODER;
    uint32_t OTYPER;
    uint32_t OSPEEDR;
    uint32_t PUPDR;
    uint32_t IDR;
    uint32_t ODR;
    uint32_t BSRR;
} GPIO_TypeDef;

// Pin mode
typedef enum {
    GPIO_MODE_INPUT     = 0,
    GPIO_MODE_OUTPUT    = 1,
    GPIO_MODE_ALTFN     = 2,
    GPIO_MODE_ANALOG    = 3
} GPIO_Mode_t;

// Output type
typedef enum {
    GPIO_OTYPE_PUSHPULL  = 0,
    GPIO_OTYPE_OPENDRAIN = 1
} GPIO_OType_t;

// Output speed
typedef enum {
    GPIO_SPEED_LOW      = 0,
    GPIO_SPEED_MEDIUM   = 1,
    GPIO_SPEED_HIGH     = 2,
    GPIO_SPEED_VERY_HIGH = 3
} GPIO_Speed_t;

// Pull up/down
typedef enum {
    GPIO_PUPD_NOPULL   = 0,
    GPIO_PUPD_PULLUP   = 1,
    GPIO_PUPD_PULLDOWN = 2
} GPIO_PuPd_t;

// Pin state
typedef enum {
    GPIO_PIN_LOW  = 0,
    GPIO_PIN_HIGH = 1
} GPIO_PinState_t;

// RCC register struct — clock control
typedef struct {
    uint32_t AHB1ENR;
    uint32_t APB1ENR;
    uint32_t APB2ENR;
} RCC_TypeDef;

// Function prototypes
void GPIO_ConfigPin(GPIO_TypeDef *port, uint8_t pin, GPIO_Mode_t mode, GPIO_OType_t otype, GPIO_Speed_t speed, GPIO_PuPd_t pupd);

void GPIO_WritePin(GPIO_TypeDef *port, uint8_t pin, GPIO_PinState_t state);

GPIO_PinState_t GPIO_ReadPin(GPIO_TypeDef *port, uint8_t pin);

void print_gpio_state(GPIO_TypeDef *port, char *name);

#endif