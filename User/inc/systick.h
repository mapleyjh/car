#ifndef __SYSTICK_H_
#define __SYSTICK_H_

//ͷ�ļ�
#include "stm32f4xx.h"

//�궨��

//��������
void Systick_Init(void);
void delay_us(u32 nus);
void delay_ms(u32 nms);
void delay_s(u32 ns);


#endif
