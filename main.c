#include <stdint.h>

#define REG32(addr) (*(volatile uint32_t *)(addr))

#define RCC_AHBENR  REG32(0x4002381C)

#define GPIOA_MODER REG32(0x40020000)
#define GPIOA_OTYPER REG32(0x40020004)
#define GPIOA_OSPEEDR REG32(0x40020008)
#define GPIOA_PUPDR REG32(0x4002000C)
#define GPIOA_ODR REG32(0x40020014)
#define GPIOA_BSRR REG32(0x40020018)

#define PA5 (1U << 5)

int main(void)
{
    // Enable GPIOA clock
    RCC_AHBENR |= (1U << 0);

    // PA5 = General purpose output (01)
    GPIOA_MODER &= ~(3U << (5 * 2));
    GPIOA_MODER |=  (1U << (5 * 2));

    // Push-pull
    GPIOA_OTYPER &= ~PA5;

    // High speed
    GPIOA_OSPEEDR |= (3U << (5 * 2));

    // No pull-up / pull-down
    GPIOA_PUPDR &= ~(3U << (5 * 2));

    while (1)
    {
        // PA5 HIGH
        GPIOA_BSRR = PA5;

        for (volatile uint32_t i = 0; i < 50000; i++);

        // PA5 LOW
        //GPIOA_BSRR = (PA5 << 16);
        GPIOA_BSRR = (1U << 21);

        for (volatile uint32_t i = 0; i < 50000; i++);
    }
}
