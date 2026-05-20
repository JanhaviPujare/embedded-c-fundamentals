# 02 Memory Inspector — Pointers and Memory Exercise

## What This Program Does
A C program that makes memory and pointers visible by printing
the value, memory address and size of different variable types.
It demonstrates how variables are stored in RAM, how arrays sit
sequentially in memory, and how pointers work at the address level.

## Why This Exists
In embedded systems programming, understanding memory is critical.
Hardware registers live at specific addresses, RAM is limited, and
pointers are used in every driver and peripheral access. This exercise
makes those concepts concrete and visible rather than abstract.

## Concepts Demonstrated

**Part 1 — Basic Variable Inspection**
Shows that different data types live at different addresses in memory
and take different amounts of space.

**Part 2 — Array Memory Layout**
Shows that array elements sit sequentially in memory, with each
element's address increasing by exactly sizeof(element) bytes.
For an int array this means addresses increase by 4 each time.

**Part 3 — Pointer Demo**
Shows the relationship between a variable and a pointer to it:
- `&x` and `ptr` contain the same address
- `*ptr` and `x` give the same value
- `&ptr` is a separate address where the pointer itself lives

**Part 4 — sizeof Table**
Shows the size in bytes of every basic C data type including
fixed size embedded types from stdint.h

## Key Observations From Output
- Different types take different memory — char=1, int=4, long=8 bytes
- Array elements are always sequential — addresses increase by sizeof(type)
- A pointer is just a variable that stores an address
- uint8_t, uint16_t, uint32_t have guaranteed sizes unlike int or long
- The same value prints differently with %d vs %c — 74 vs 'J'

## Connection to Embedded Systems
| Exercise concept | Real embedded equivalent |
|---|---|
| Printing variable addresses | Hardware registers live at fixed addresses |
| sizeof different types | Choosing right type for sensor data or registers |
| Pointer stores an address | `GPIOD->ODR` accesses register at address 0x40020C14 |
| uint32_t guaranteed size | STM32 registers are always exactly 32 bits wide |
| Array sequential addresses | DMA transfers move sequential blocks of memory |

## How to Run

======================= Memory Inspector============================
| Vriable | Value | Address | Size |
|---|---|




### Option 1 — Online
1. Go to [onlinegdb.com](https://onlinegdb.com)
2. Set language to **C**
3. Paste contents of `memory_inspector.c`
4. Click **Run**

### Option 2 — VS Code
1. Open `memory_inspector.c` in VS Code
2. Press **Ctrl + Alt + N**

### Option 3 — Command Line
```bash
gcc memory_inspector.c -o memory_inspector
./memory_inspector
```
## Notes
- The most important insight from this exercise is Part 3; seeing that `&x` and `ptr` contain the exact same address proves that a pointer genuinely points to the original variable, not a copy of it. This is why functions that take pointer parameters can modify the original variable.
- Array addresses increasing by exactly 4 bytes explains pointer arithmetic — `ptr + 1` on an int pointer jumps 4 bytes, not 1.
- This exercise directly prepared the foundation for the GPIO Register Simulator in 03_bitwise_operations where pointers were used to pass GPIO port structs to functions by reference.
