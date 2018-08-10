#ifndef __KEY_H_
#define __KEY_H_

//头文件
#include "stm32f4xx.h"
#include "sys.h"
#include "led.h"
#include "systick.h"
#include "function.h"

//宏定义

//函数声明
void key_init(void);
void exti_key(void);

extern char flag;

#endif
