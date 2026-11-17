
#include <stdint.h>

/* Linker symbols */
extern uint32_t _estack;
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

/* Application entry */
extern int main(void);

/* Default interrupt handler */
void Default_Handler(void)
{
    while (1)
    {
        __asm volatile ("nop");
    }
}

/* Core exception handlers */
void Reset_Handler(void);
void NMI_Handler(void)       __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void) __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void)  __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void)__attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void)       __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void)  __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void)   __attribute__((weak, alias("Default_Handler")));

/*
 * Vector table:
 * 16 Cortex-M exception entries
 * 128 external interrupt entries
 */
__attribute__((section(".isr_vector"), used, aligned(512)))
const uintptr_t vector_table[16 + 128] =
{
    [0]  = (uintptr_t)&_estack,
    [1]  = (uintptr_t)Reset_Handler,
    [2]  = (uintptr_t)NMI_Handler,
    [3]  = (uintptr_t)HardFault_Handler,
    [4]  = (uintptr_t)MemManage_Handler,
    [5]  = (uintptr_t)BusFault_Handler,
    [6]  = (uintptr_t)UsageFault_Handler,
    [11] = (uintptr_t)SVC_Handler,
    [12] = (uintptr_t)DebugMon_Handler,
    [14] = (uintptr_t)PendSV_Handler,
    [15] = (uintptr_t)SysTick_Handler
};

/* Reset handler */
void Reset_Handler(void)
{
    uint32_t *src;
    uint32_t *dst;

    /* Copy .data from Flash to RAM */
    src = &_sidata;
    dst = &_sdata;

    while (dst < &_edata)
    {
        *dst++ = *src++;
    }

    /* Clear .bss */
    dst = &_sbss;

    while (dst < &_ebss)
    {
        *dst++ = 0;
    }

    /* Start application */
    (void)main();

    /* main() should never return */
    while (1)
    {
        __asm volatile ("nop");
    }
}
