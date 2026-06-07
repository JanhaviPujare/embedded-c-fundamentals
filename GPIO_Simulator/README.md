# 03 GPIO Register Simulator

## What This Program Does
This program is a virtual simulation of a GPIO register on an ARM 
Cortex-M microcontroller. It simulates MODER, IDR and ODR to mimic 
the behaviour of pins in a GPIO register.

## Why This Project Exists
In real microcontroller programming, in order to execute a task using 
a microcontroller, there is often a need to properly configure the 
registers and pins on the board. This project not only teaches how to 
configure microcontrollers in real life, but also shows the inner 
workings of a microcontroller after a user has configured it, due to 
the virtual simulation of a register using pure C programming.

## Concepts Covered
- **Bitwise Operators** — used to manipulate individual bits of a register
- **Macros** — used to define reusable bit manipulation operations
- **Structs** — used to group the three GPIO registers into one data type
- **Pointers** — used to pass GPIO port structs to functions by reference
- **Functions** — used to wrap macros into reusable, readable operations
- **Looping Statements** — used in the menu loop and pin state display

## The Four Core Macros
There are 4 macros in this program:
- **SET_BIT** — Sets a particular bit using the Bitwise OR operator 
  and the concept of bit masking
- **CLEAR_BIT** — Clears a particular bit using the Bitwise AND and 
  NOT operators and the concept of bit masking
- **TOGGLE_BIT** — Toggles a bit from 0 to 1 or vice versa using 
  the Bitwise XOR operator
- **READ_BIT** — Shifts the register right by the pin number and then 
  AND's with 1U to extract just that bit as a 0 or 1

## GPIO Structure
The GPIO_Port_t structure is a user defined struct which defines 3 
unsigned 32-bit registers for each GPIO port:
- **MODER** — Mode Register. Used to configure each pin as input or 
  output. Each pin uses 2 bits — 00 for input, 01 for output
- **IDR** (Input Data Register) — Read only register that reflects 
  the current signal present on input pins
- **ODR** (Output Data Register) — Write register that controls the 
  output state of pins configured as output

## How The Functions Work
- **gpio_pin_mode()** — Uses the port pointer and MODER register to 
  first clear the 2 bits for the selected pin, then set the mode. 
  Mirrors how the real STM32 MODER register is configured
- **gpio_set()** — Checks whether the pin is configured as OUTPUT 
  using READ_BIT on MODER, then sets the pin HIGH in ODR. Prints 
  an error if the pin is configured as INPUT
- **gpio_clear()** — Checks whether the pin is configured as OUTPUT, 
  then clears the pin LOW in ODR. Prints an error if INPUT
- **gpio_toggle()** — Checks mode then toggles the selected pin in 
  ODR from HIGH to LOW or LOW to HIGH using XOR
- **gpio_read_input()** — Checks MODER to determine if the pin is 
  OUTPUT or INPUT, then reads from ODR or IDR accordingly and 
  returns the pin state as 0 or 1
- **gpio_clear_all()** — Clears all pins of the entire port at once 
  by directly assigning ODR to 0x00000000
- **gpio_simulate_input()** — Simulates an external signal arriving 
  on an input pin by directly writing to IDR. This function only 
  exists because this is a simulation — on real hardware, IDR is 
  updated automatically by the physical voltage on the pin
- **print_port_state()** — Prints the current value of all 3 
  registers (MODER, ODR, IDR) for the selected port in hexadecimal, 
  and displays each pin's state as a binary string from pin 7 to pin 0

## How to Run

### Option 1 — Online (no setup required)
1. Go to [onlinegdb.com](https://onlinegdb.com)
2. Set language to **C**
3. Paste the contents of `gpio_simulator.c`
4. Click **Run**

### Option 2 — VS Code with GCC
1. Install [VS Code](https://code.visualstudio.com)
2. Install the **Code Runner** extension by Jun Han
3. Open `gpio_simulator.c` in VS Code
4. Press **Ctrl + Alt + N** to compile and run

### Option 3 — Command Line
```bash
gcc gpio_simulator.c -o gpio_simulator
./gpio_simulator
```

## How This Connects to Real Hardware

This simulation directly mirrors how real STM32 GPIO registers work:

| Simulation | Real Hardware |
|---|---|
| `GPIO_Port_t` struct | Real GPIO peripheral registers at a fixed memory address |
| `gpio_pin_mode()` | Writing to GPIOx_MODER register |
| `gpio_set()` | Writing 1 to a bit in GPIOx_ODR |
| `gpio_clear()` | Writing 0 to a bit in GPIOx_ODR |
| `gpio_toggle()` | XOR operation on GPIOx_ODR |
| `gpio_read_input()` | Reading GPIOx_IDR for inputs, GPIOx_ODR for outputs |
| `gpio_simulate_input()` | What real hardware does automatically from physical pin voltage |

The key difference is that in real hardware the registers exist at 
specific memory addresses (e.g. GPIOD base address is 0x40020C00) 
and are accessed through pointers to those addresses. The same `->` 
pointer syntax used in this simulation is used in real STM32 driver 
code — for example `GPIOD->ODR |= (1 << 12)` to turn on an LED.

## Sample Output

===== GPIO Register Simulator =====
STM32F4 GPIO Register Simulator
All ports start with all pins LOW

===== GPIO Simulator Menu =====
1. Configure pin mode
2. Set pin HIGH
3. Clear pin LOW
4. Toggle pin
5. Read pin state
6. Clear all pins
7. Print port state
0. Exit
Enter choice: 1
Select port:
1. GPIOA
2. GPIOB
3. GPIOC
Enter choice: 1
Enter pin number (0-7): 6
Enter mode (0=INPUT, 1=OUTPUT): 1
Pin 6 configured as OUTPUT

===== GPIO Simulator Menu =====
1. Configure pin mode
2. Set pin HIGH
3. Clear pin LOW
4. Toggle pin
5. Read pin state
6. Clear all pins
7. Print port state
0. Exit
Enter choice: 2
Select port:
1. GPIOA
2. GPIOB
3. GPIOC
Enter choice: 1
Enter pin number (0-7): 6
SET   pin 6 --> ODR: 0x00000040

===== GPIO Simulator Menu =====
1. Configure pin mode
2. Set pin HIGH
3. Clear pin LOW
4. Toggle pin
5. Read pin state
6. Clear all pins
7. Print port state
0. Exit
Enter choice: 1
Select port:
1. GPIOA
2. GPIOB
3. GPIOC
Enter choice: 1
Enter pin number (0-7): 4
Enter mode (0=INPUT, 1=OUTPUT): 1
Pin 4 configured as OUTPUT

===== GPIO Simulator Menu =====
1. Configure pin mode
2. Set pin HIGH
3. Clear pin LOW
4. Toggle pin
5. Read pin state
6. Clear all pins
7. Print port state
0. Exit
Enter choice: 2
Select port:
1. GPIOA
2. GPIOB
3. GPIOC
Enter choice: 1
Enter pin number (0-7): 4
SET   pin 4 --> ODR: 0x00000050

===== GPIO Simulator Menu =====
1. Configure pin mode
2. Set pin HIGH
3. Clear pin LOW
4. Toggle pin
5. Read pin state
6. Clear all pins
7. Print port state
0. Exit
Enter choice: 5
Select port:
1. GPIOA
2. GPIOB
3. GPIOC
Enter choice: 1
Enter pin number (0-7): 6
Pin 6 state: 1

===== GPIO Simulator Menu =====
1. Configure pin mode
2. Set pin HIGH
3. Clear pin LOW
4. Toggle pin
5. Read pin state
6. Clear all pins
7. Print port state
0. Exit
Enter choice: 7
Select port:
1. GPIOA
2. GPIOB
3. GPIOC
Enter choice: 1

--- GPIOA State ---
MODER: 0x00001100
ODR:   0x00000050
IDR:   0x00000000
Pin states (ODR): 01010000 (pin7 to pin0)
--------------------

## Notes

- The most important concept this project taught was the difference between ODR and IDR — output pins are written to and read from ODR, 
  while input pins are read from IDR which is updated by the outside world
  
- Pointers were used so that functions modify the actual GPIO port struct rather than a copy — without pointers, none of the register 
  changes would persist after the function returned
  
- The `->` operator is used to access struct fields through a pointer; 'port->ODR` means "go to the address stored in port and access ODR"

- This project is a foundation for real STM32 register-level programming 
 
