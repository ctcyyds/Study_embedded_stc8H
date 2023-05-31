#include <STC8H.H>
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



int main() {
    // 0xEF
    // B7 |B6 |B5 |B4 |B3 |B2|B1|B0
    // 1	| 1 |1  | 0 | 1 |1 |1 |17
    // 1	| 1 |1  | 1 | 0 |1 |1 |1   &
    // 1	| 1 |1  | 0 | 0 |1 |1 |1

    // 0	| 0 |0  | 0 | 1 |0 |0 |0
    // 1	| 1 |1  | 0 | 0 |1 |1 |1   期望值
    //P5M1 &=~ 0x08; P5M0 &= ~0x08;//准双向口
    //P5M1 &= ~0x08; P5M0 |= 0x08;//推挽输出
    //P5M1 |= 0x08; P5M0 &= ~0x08;//高阻输入
      P5M1 |= 0x08; P5M0 |= 0x08;//开漏
    
    while(1) {
        P53=1;
        Delay1000ms();
        P53=0;
        Delay1000ms();
    }

}