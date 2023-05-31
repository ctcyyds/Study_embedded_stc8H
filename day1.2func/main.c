#include "config.h"
#include "GPIO.h"

void Delay1000ms()		//@11.0592MHz
{
    unsigned char i, j, k;

    i = 57;
    j = 27;
    k = 112;
    do
    {
        do
        {
            while (--k);
        } while (--j);
    } while (--i);
}

//P53
void GPIO_config() {
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Mode=GPIO_PullUp;
    GPIO_InitStructure.Pin=GPIO_Pin_3;
    GPIO_Inilize(GPIO_P5, &GPIO_InitStructure);
}

int main() {
    //I/O¿ÚÄ£Ê½
    GPIO_config();
    while(1) {
        P53=1;
        Delay1000ms();
        P53=0;
        Delay1000ms();
    }
}