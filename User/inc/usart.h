#ifndef __USART_H_
#define __USART_H_
#include "stm32f4xx.h"
#include "stdio.h"


#define USART_REC_LEN  			200  		//定义最大接收字节数200
#define EN_USART1_RX 			1		//使能(1)/禁止(0)串口1接收


typedef unsigned int u32;
typedef unsigned char u8;

enum {lefta = 1,leftb = 2,righta = 3,rightb = 4};		//pwm_state

// 
#define left_a PCout(6)						// CAMERA_D17 
#define left_b PCout(7)						// CAMERA_D18	
#define right_a PCout(8)						// CAMERA_D15	
#define right_b PCout(9)

	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲，最大USART_REC_LEN个字节，末字节为换行符
extern u16 USART_RX_STA;         		//接收状态标志	
extern char recvbuf;						// 串口接收有效字符
extern char recvend;						// 接收完成标志

//如果想串口中断接收，请不要注释以下宏定义
void Uart1_init(u32 bound);
void Uart2_init(u32 bound);

#endif
