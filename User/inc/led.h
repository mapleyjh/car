#ifndef __LED_H_
#define __LED_H_

//ͷ�ļ�
#include "stm32f4xx.h"
#include "key.h"
#include "sys.h"
#include "systick.h"

//�궨��

#define	LED1_ON	 GPIO_WriteBit(GPIOF,GPIO_Pin_9,0);//LED1��
#define	LED1_OFF  GPIO_WriteBit(GPIOF,GPIO_Pin_9,1);//LED1��
#define	LED2_ON	 GPIO_WriteBit(GPIOF,GPIO_Pin_10,0);//LED2��
#define	LED2_OFF  GPIO_WriteBit(GPIOF,GPIO_Pin_10,1);//LED2��
#define	LED3_ON	 GPIO_WriteBit(GPIOE,GPIO_Pin_13,0);//LED3��
#define	LED3_OFF  GPIO_WriteBit(GPIOE,GPIO_Pin_13,1);//LED3��
#define	LED4_ON	 GPIO_WriteBit(GPIOE,GPIO_Pin_14,0);//LED4��
#define	LED4_OFF  GPIO_WriteBit(GPIOE,GPIO_Pin_14,1);//LED4��

//��������
void led_init(void);


#endif
