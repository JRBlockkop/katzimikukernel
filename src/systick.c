#include <stdint.h>

#define SYST_CSR  (*(volatile uint32_t*)0xE000E010)
#define SYST_RVR  (*(volatile uint32_t*)0xE000E014)
#define SYST_CVR  (*(volatile uint32_t*)0xE000E018)

void systick_init(void)
{
    // 1 ms bei 4.194304 MHz MSI
    SYST_RVR = 4194 - 1;

    SYST_CVR = 0;

    // Enable | Processor Clock | No Interrupt
    SYST_CSR = (1U << 0) | (1U << 2);
}

void delay_ms(uint32_t ms)
{
    while (ms--)
    {
        while (!(SYST_CSR & (1U << 16)));
    }
}
