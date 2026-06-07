#include <stdio.h>
#include <stdint.h>

// The 4 core macros
#define SET_BIT(reg, pin)    ((reg) |=  (1U << (pin)))
#define CLEAR_BIT(reg, pin)  ((reg) &= ~(1U << (pin)))
#define TOGGLE_BIT(reg, pin) ((reg) ^=  (1U << (pin)))
#define READ_BIT(reg, pin)   (((reg) >> (pin)) & 1U)

// Pin mode definitions
#define GPIO_MODE_INPUT    0U
#define GPIO_MODE_OUTPUT   1U

// GPIO port structure
typedef struct {
    uint32_t ODR;
    uint32_t IDR;
    uint32_t MODER;
} GPIO_Port_t;

// Three simulated GPIO ports
GPIO_Port_t GPIOA = {0, 0, 0};
GPIO_Port_t GPIOB = {0, 0, 0};
GPIO_Port_t GPIOC = {0, 0, 0};

// --- All previous functions ---

void gpio_pin_mode(GPIO_Port_t *port, uint8_t pin, uint8_t mode) {
    port->MODER &= ~(3U << (pin * 2));
    port->MODER |=  (mode << (pin * 2));
}

void gpio_set(GPIO_Port_t *port, uint8_t pin) {
    if(READ_BIT(port->MODER, pin * 2) == GPIO_MODE_OUTPUT) {
        SET_BIT(port->ODR, pin);
        printf("SET   pin %d --> ODR: 0x%08X\n", pin, port->ODR);
    } else {
        printf("ERROR: pin %d is not configured as OUTPUT\n", pin);
    }
}

void gpio_clear(GPIO_Port_t *port, uint8_t pin) {
    if(READ_BIT(port->MODER, pin * 2) == GPIO_MODE_OUTPUT) {
        CLEAR_BIT(port->ODR, pin);
        printf("CLEAR pin %d --> ODR: 0x%08X\n", pin, port->ODR);
    } else {
        printf("ERROR: pin %d is not configured as OUTPUT\n", pin);
    }
}

void gpio_toggle(GPIO_Port_t *port, uint8_t pin) {
    if(READ_BIT(port->MODER, pin * 2) == GPIO_MODE_OUTPUT) {
        TOGGLE_BIT(port->ODR, pin);
        printf("TOGGLE pin %d --> ODR: 0x%08X\n", pin, port->ODR);
    } else {
        printf("ERROR: pin %d is not configured as OUTPUT\n", pin);
    }
}

uint8_t gpio_read_input(GPIO_Port_t *port, uint8_t pin) {
    if(READ_BIT(port->MODER, pin * 2) == GPIO_MODE_OUTPUT) {
        return READ_BIT(port->ODR, pin);   // output pin → read ODR
    } else {
        return READ_BIT(port->IDR, pin);   // input pin → read IDR
    }
}

void gpio_clear_all(GPIO_Port_t *port) {
    port->ODR = 0x00000000;
    printf("All pins cleared --> ODR: 0x%08X\n", port->ODR);
}

void print_port_state(GPIO_Port_t *port, char *port_name) {
    printf("\n--- %s State ---\n", port_name);
    printf("MODER: 0x%08X\n", port->MODER);
    printf("ODR:   0x%08X\n", port->ODR);
    printf("IDR:   0x%08X\n", port->IDR);
    printf("Pin states (ODR): ");
    for(int i = 7; i >= 0; i--) {
        printf("%d", READ_BIT(port->ODR, i));
    }
    printf(" (pin7 to pin0)\n");
    printf("--------------------\n\n");
}

// --- New helper: select port from user input ---

GPIO_Port_t* select_port(int port_choice) {
    if(port_choice == 1) return &GPIOA;
    if(port_choice == 2) return &GPIOB;
    if(port_choice == 3) return &GPIOC;
    return NULL;
}

char* port_name(int port_choice) {
    if(port_choice == 1) return "GPIOA";
    if(port_choice == 2) return "GPIOB";
    if(port_choice == 3) return "GPIOC";
    return "UNKNOWN";
}

// --- Menu functions ---

void display_menu(void) {
    printf("\n===== GPIO Simulator Menu =====\n");
    printf("1. Configure pin mode\n");
    printf("2. Set pin HIGH\n");
    printf("3. Clear pin LOW\n");
    printf("4. Toggle pin\n");
    printf("5. Read pin state\n");
    printf("6. Clear all pins\n");
    printf("7. Print port state\n");
    printf("0. Exit\n");
    printf("Enter choice: ");
}

void display_port_menu(void) {
    printf("Select port:\n");
    printf("1. GPIOA\n");
    printf("2. GPIOB\n");
    printf("3. GPIOC\n");
    printf("Enter choice: ");
}

// --- Main ---

int main(void) {

    int menu_choice;
    int port_choice;
    int pin;
    int mode;
    GPIO_Port_t *port;

    printf("===== GPIO Register Simulator =====\n");
    printf("STM32F4 GPIO Register Simulator\n");
    printf("All ports start with all pins LOW\n");

    while(1) {

        // Show menu and get choice
        display_menu();
        scanf("%d", &menu_choice);

        // Exit condition
        if(menu_choice == 0) {
            printf("Exiting simulator.\n");
            break;
        }

        // For options 1-7, ask which port
        display_port_menu();
        scanf("%d", &port_choice);
        port = select_port(port_choice);

        // Invalid port check
        if(port == NULL) {
            printf("Invalid port selection.\n");
            continue;
        }

        // Handle menu choice
        switch(menu_choice) {

            case 1:
                printf("Enter pin number (0-7): ");
                scanf("%d", &pin);
                printf("Enter mode (0=INPUT, 1=OUTPUT): ");
                scanf("%d", &mode);
                gpio_pin_mode(port, pin, mode);
                printf("Pin %d configured as %s\n",
                       pin, mode ? "OUTPUT" : "INPUT");
                break;

            case 2:
                printf("Enter pin number (0-7): ");
                scanf("%d", &pin);
                gpio_set(port, pin);
                break;

            case 3:
                printf("Enter pin number (0-7): ");
                scanf("%d", &pin);
                gpio_clear(port, pin);
                break;

            case 4:
                printf("Enter pin number (0-7): ");
                scanf("%d", &pin);
                gpio_toggle(port, pin);
                break;

            case 5:
                printf("Enter pin number (0-7): ");
                scanf("%d", &pin);
                printf("Pin %d state: %d\n",
                       pin, gpio_read_input(port, pin));
                break;

            case 6:
                gpio_clear_all(port);
                break;

            case 7:
                print_port_state(port, port_name(port_choice));
                break;

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}