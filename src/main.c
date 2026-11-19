#include <stdint.h>
#include "systick.h"

#define REG32(addr) (*(volatile uint32_t *)(addr))

#define RCC_AHBENR   REG32(0x4002381C)

#define GPIOA_MODER  REG32(0x40020000)
#define GPIOA_OTYPER REG32(0x40020004)
#define GPIOA_OSPEEDR REG32(0x40020008)
#define GPIOA_PUPDR  REG32(0x4002000C)
#define GPIOA_BSRR   REG32(0x40020018)

#define PA5 (1U << 5)

static void delay(void)
{
    for (volatile uint32_t i = 0; i < 5000000; i++);
}

int main(void)
{
    // GPIOA Clock
    RCC_AHBENR |= (1U << 0);

    // PA5 Output
    GPIOA_MODER &= ~(3U << 10);
    GPIOA_MODER |=  (1U << 10);

    // Push-Pull
    GPIOA_OTYPER &= ~PA5;

    // High Speed
    GPIOA_OSPEEDR |= (3U << 10);

    // No Pull
    GPIOA_PUPDR &= ~(3U << 10);

    systick_init();

    while (1)
    {
        // LED ON
        GPIOA_BSRR = PA5;

        delay_ms(500);

        // LED OFF
        GPIOA_BSRR = (PA5 << 16);

        delay_ms(500);
    }
}
