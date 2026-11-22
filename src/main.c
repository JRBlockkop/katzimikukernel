#include <stdint.h>
#include "systick.h"
#include "gpio.h"

int main(void)
{
    systick_init();

    while (1)
    {
        delay_ms(1);
    }
}
