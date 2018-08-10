#ifndef  _FUNCTION_H_  
#define _FUNCTION_H_ 

//ͷ�ļ�
#include "stm32f4xx.h"
#include "systick.h"
#include "sys.h"
#include "led.h"
#include "key.h"
#include "beep.h"
#include "function.h"
#include "tim.h"
#include "pwm.h"
#include "motor.h"
#include "usart.h"
#include "hc.h"

//�궨��
extern int function_mode;//1 ���ù��� 2 �鿴����
extern int set_type;//1 ����ʱ  2 ���÷ֵ�ʮλ  3 ���÷ֵĸ�λ 4 �������

extern int look_type;//1 �鿴ʱ  2 �鿴�ֵ�ʮλ  3 �鿴�ֵĸ�λ

extern int h,m,s;//��¼��ǰʱ���� ��ʼ��ʱ��Ϊ  8��29��00
extern int c_h,c_m,c_s;//��¼����ʱ����
extern int c_m_gw,c_m_sw;//��¼�ָ�λ ʮλ

extern int on_time;//0 ʱ��δ�� 1 ʱ�䵽

//��������
void led_Stopwatch(void);
void led_show(unsigned int a);
void motor(void);
	
extern char flag;


#endif
