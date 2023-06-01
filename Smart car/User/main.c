
#include "GPIO.h"
#include "UART.h"
#include <stdio.h>
#include "Key.h"
#include "Motors.h"
#include "Track.h"


u8 flag = 0;
char putchar (char dat) {
    TX1_write2buff(dat);
    return dat;
}

void GPIO_config(void) {
	GPIO_InitTypeDef	GPIO_InitStructure;		//�ṹ����
	GPIO_InitStructure.Pin  = GPIO_Pin_0 | GPIO_Pin_1;		//ָ��Ҫ��ʼ����IO,
	GPIO_InitStructure.Mode = GPIO_PullUp;	//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P3, &GPIO_InitStructure);//��ʼ��
}

void UART_config(void) {
    COMx_InitDefine		COMx_InitStructure;					//�ṹ����
    COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;	//ģʽ, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;			//ѡ�����ʷ�����, BRT_Timer1, BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2)
    COMx_InitStructure.UART_BaudRate  = 115200ul;			//������, һ�� 110 ~ 115200
    COMx_InitStructure.UART_RxEnable  = ENABLE;				//��������,   ENABLE��DISABLE
    COMx_InitStructure.BaudRateDouble = DISABLE;			//�����ʼӱ�, ENABLE��DISABLE
    COMx_InitStructure.UART_Interrupt = ENABLE;				//�ж�����,   ENABLE��DISABLE
    COMx_InitStructure.UART_Priority  = Priority_0;			//ָ���ж����ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
    COMx_InitStructure.UART_P_SW      = UART1_SW_P30_P31;	//�л��˿�,   UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17,UART1_SW_P43_P44
    UART_Configuration(UART1, &COMx_InitStructure);		//��ʼ������1 UART1,UART2,UART3,UART4
}



void sys_init() {
    GPIO_config();
    UART_config();

    Key_init();
    Motors_init();
    Track_init();
    EA = 1;
}

// �����ҵĳ������
void start() _task_ 0 {
    sys_init();

    os_create_task(1);
    os_delete_task(0);
}

void Key_on_keyup() {
    if(flag == 0) {
				printf("����Ѳ��\r\n");
        // ��һ������Ѳ������
				os_create_task(2);
    } else {
			printf("ֹͣѲ��\r\n");
				os_delete_task(2);
        // �ٰ�ֹͣ
        Motors_stop();
    }
		flag = !flag;
}
void Key_on_keydown() {

}

// ɨ�谴��״̬
void task1() _task_ 1 {
    while(1) {
        Key_scan();
        os_wait2(K_TMO, 4);
    }
}

// ʵʱ��ȡ�ߵ�������Ϣ
void task2() _task_ 2 {
		int pos;
		printf("task2 start\r\n");
    while(1) {
				Track_get_position(&pos);
				
				// �ж�����
				if(pos == 0) {
					// ֱ��
					Motors_forward(80);
				} else if(pos < 0) {
					// ���
					Motors_left(50);
				} else if(pos > 0) {
					Motors_right(50);
				}
        os_wait2(K_TMO, 1);
    }
}