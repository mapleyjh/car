#ifndef __USART_H_
#define __USART_H_
#include "stm32f4xx.h"
#include "stdio.h"


#define USART_REC_LEN  			200  		//�����������ֽ���200
#define EN_USART1_RX 			1		//ʹ��(1)/��ֹ(0)����1����


typedef unsigned int u32;
typedef unsigned char u8;

enum {lefta = 1,leftb = 2,righta = 3,rightb = 4};		//pwm_state

// 
#define left_a PCout(6)						// CAMERA_D17 
#define left_b PCout(7)						// CAMERA_D18	
#define right_a PCout(8)						// CAMERA_D15	
#define right_b PCout(9)

	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ��壬���USART_REC_LEN���ֽڣ�ĩ�ֽ�Ϊ���з�
extern u16 USART_RX_STA;         		//����״̬��־	
extern char recvbuf;						// ���ڽ�����Ч�ַ�
extern char recvend;						// ������ɱ�־

//����봮���жϽ��գ��벻Ҫע�����º궨��
void Uart1_init(u32 bound);
void Uart2_init(u32 bound);

#endif
