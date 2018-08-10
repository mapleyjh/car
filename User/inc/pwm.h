#ifndef __PWM_H_
#define __PWM_H_

//头文件
#include "stm32f4xx.h"
#include "sys.h"
#include "tim.h"
#include "motor.h"


//宏定义

//函数声明
void GPIO_PF9init(void);
//void MOTORGPIO_Pin6789_init(void);
void pwm_init(void);

void GPIO_PF8init(void);
void tim13_init(void);
void tim13_pwm_init(void);


#endif
