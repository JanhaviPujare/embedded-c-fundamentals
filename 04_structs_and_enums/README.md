# 04 Peripheral Register Map Simulator

## What This Project Does
A multi-file C program that models real STM32F4 peripheral registers
using structs and enums. It simulates configuring a GPIO output pin
(LED) and input pin (button) through a structured driver interface,
demonstrating how real STM32 HAL drivers are architected internally.

## Why This Project Exists
Every STM32 peripheral is represented as a struct in the HAL library.
Understanding how those structs are defined and how functions write
to their register fields is essential for embedded systems programming.
This project builds that understanding by creating a near-identical
simulation of the real STM32 GPIO and RCC peripheral structures.

## File Structure
04_structs_and_enums/
├── peripheral_map.h    — struct definitions, enums, function prototypes
├── peripheral_map.c    — driver function implementations
└── main.c              — demonstration program

## Concepts Covered
- **Structs** — modelling peripheral registers as grouped data types
- **Enums** — replacing magic numbers with readable configuration options
- **Header files** — separating declarations from implementations
- **Multi-file compilation** — splitting a project across multiple .c files
- **Header guards** — preventing double inclusion with #ifndef/#define/#endif
- **Function prototypes** — declaring functions before they are defined
- **Pointers to structs** — passing peripherals by reference using ->
- **Bitwise operations** — writing to specific register bits

## Peripheral Structures Modelled

### GPIO_TypeDef
Models the complete STM32 GPIO register set:

| Register | Purpose |
|---|---|
| MODER | Pin mode — input, output, alternate function, analog |
| OTYPER | Output type — push-pull or open-drain |
| OSPEEDR | Output speed — low, medium, high, very high |
| PUPDR | Pull-up/pull-down resistor configuration |
| IDR | Input Data Register — reads pin state |
| ODR | Output Data Register — controls output pins |
| BSRR | Bit Set/Reset Register |

### RCC_TypeDef
Models the STM32 clock enable registers:

| Register | Purpose |
|---|---|
| AHB1ENR | Enables clocks for GPIO peripherals |
| APB1ENR | Enables clocks for UART, SPI, I2C (APB1 bus) |
| APB2ENR | Enables clocks for UART1, SPI1, Timers (APB2 bus) |

## Enums Used

| Enum | Values |
|---|---|
| GPIO_Mode_t | INPUT, OUTPUT, ALTFN, ANALOG |
| GPIO_OType_t | PUSHPULL, OPENDRAIN |
| GPIO_Speed_t | LOW, MEDIUM, HIGH, VERY_HIGH |
| GPIO_PuPd_t | NOPULL, PULLUP, PULLDOWN |
| GPIO_PinState_t | LOW, HIGH |

## Driver Functions

| Function | Purpose |
|---|---|
| GPIO_ConfigPin() | Configures MODER, OTYPER, OSPEEDR, PUPDR for a pin |
| GPIO_WritePin() | Sets or clears a pin in ODR |
| GPIO_ReadPin() | Reads pin state from IDR |
| print_gpio_state() | Prints all register values for a port |

## What the Program Demonstrates

**Step 1 — Clock Enable**
Sets bits in RCC_AHB1ENR to enable GPIOA and GPIOB clocks.
On real STM32 hardware this is mandatory before touching any GPIO.

**Step 2 — Output Pin Configuration**
Configures PA5 as push-pull output at low speed with no pull resistor.
MODER shows 0x00000400 — value 01 at bits 11:10 (pin 5 × 2 = 10).

**Step 3 — Input Pin Configuration**
Configures PB13 as input with pull-up resistor enabled.
PUPDR shows 0x04000000 — value 01 at bits 27:26 (pin 13 × 2 = 26).

**Step 4 — LED Control**
Writes HIGH and LOW to ODR bit 5 — ODR toggles between
0x00000020 (ON) and 0x00000000 (OFF).

**Step 5 — Button Read**
Simulates external signal on IDR bit 13 and reads it back
correctly as LOW (not pressed) and HIGH (pressed).

## How to Compile and Run

```bash
gcc main.c peripheral_map.c -o peripheral_map
./peripheral_map.exe
```

Note: all source files must be passed to GCC together since
the project spans multiple files.

## Connection to Real STM32 Hardware

| This Simulation | Real STM32 HAL |
|---|---|
| `GPIO_TypeDef GPIOA = {0...}` | `#define GPIOA ((GPIO_TypeDef*)0x40020000)` |
| `GPIOA.ODR` | `GPIOA->ODR` |
| `GPIO_ConfigPin()` | `HAL_GPIO_Init()` |
| `GPIO_WritePin()` | `HAL_GPIO_WritePin()` |
| `GPIO_ReadPin()` | `HAL_GPIO_ReadPin()` |
| `RCC.AHB1ENR \|= (1<<0)` | `__HAL_RCC_GPIOA_CLK_ENABLE()` |

The only difference between this simulation and real hardware
is that real peripherals are accessed through pointers to fixed
memory addresses instead of local struct variables.

## Notes
- The most important lesson from this project is that the STM32
  HAL library is just structs and bitwise operations — exactly
  what this simulation uses. There is no magic inside HAL.
- Header guards (#ifndef/#define/#endif) are essential in
  multi-file projects to prevent structs being defined twice
  when multiple files include the same header.
- Function prototypes in the header file tell main.c that
  these functions exist before it sees their full definition
  in peripheral_map.c — without them the compiler warns
  about implicit declarations.
- The -> operator is used throughout because functions receive
  pointers to GPIO structs, not copies of them. Without pointers
  register changes would not persist after the function returns.
