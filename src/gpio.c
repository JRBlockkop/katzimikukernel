#include <stdint.h>

#define REG32(addr) (*(volatile uint32_t *)(addr))

#define RCC_AHBENR   REG32(0x4002381C)

#define GPIOA_MODER  REG32(0x40020000)
#define GPIOA_OTYPER REG32(0x40020004)
#define GPIOA_OSPEEDR REG32(0x40020008)
#define GPIOA_PUPDR  REG32(0x4002000C)
#define GPIOA_BSRR   REG32(0x40020018)

#define GPIOC_MODER  REG32(0x40020800)
#define GPIOC_PUPDR  REG32(0x4002080C)
#define GPIOC_IDR    REG32(0x40020810)

void gpio_output_init(int n)
{
    RCC_AHBENR |= (1U << 0);

    GPIOA_MODER &= ~(3U << (2 * n));
    GPIOA_MODER |=  (1U << (2 * n));

    GPIOA_OTYPER &= ~(1U << n);

    GPIOA_OSPEEDR |= (3U << (2 * n));

    GPIOA_PUPDR &= ~(3U << (2 * n));
}

void gpio_on(int n)
{
    GPIOA_BSRR = (1U << n);
}

void gpio_off(int n)
{
    GPIOA_BSRR = ((1U << n) << 16);
}

void gpio_input_init(int n)
{
    RCC_AHBENR |= (1U << 2);

    GPIOC_MODER &= ~(3U << (2 * n));

    GPIOC_PUPDR &= ~(3U << (2 * n));
}

int gpio_read(int n)
{
    return (GPIOC_IDR & (1U << n)) != 0;
}

