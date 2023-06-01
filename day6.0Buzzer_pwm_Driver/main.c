#include "config.h"
#include "delay.h"
#include "PWM.h"
#include "Buzzer.h"

int main()
{
    u8 i;
    Buzzer_init();
    EA = 1;

        while (1)
    {
        for (i = 0; i < 8; i++)
        {
            Buzzer_music(i+1);
            delay_ms(250);
            delay_ms(250);
            delay_ms(250);
            delay_ms(250);
        }
    }
}