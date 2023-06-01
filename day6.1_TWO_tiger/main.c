#include "config.h"
#include "delay.h"
#include "PWM.h"
#include "Buzzer.h"

// Òô
u8 notes[] = {
    1, 2, 3, 1,
    1, 2, 3, 1,
    3, 4, 5,
    3, 4, 5,
    5, 6, 5, 4, 3, 1,
    5, 6, 5, 4, 3, 1,
    1, 5, 1,
    1, 5, 1};

// ½Ú×à
u8 steps[] = {
    4, 4, 4, 4,
    4, 4, 4, 4,
    4, 4, 8,
    4, 4, 8,
    3, 1, 3, 1, 4, 4,
    3, 1, 3, 1, 4, 4,
    4, 4, 8,
    4, 4, 8};

int main()
{
    u16 i;
    u16 s;
    Buzzer_init();
    EA = 1;

    while (1)
    {
        for (i = 0; i < sizeof(notes) / sizeof(notes[0]); i++)
        {
            Buzzer_music(notes[i]);
            s = steps[i] * 120;
            do
            {
                delay_ms(1);
            } while (--s);
        }
    }
}