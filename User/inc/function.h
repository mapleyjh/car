#ifndef  _FUNCTION_H_  
#define _FUNCTION_H_ 

//头文件
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

//宏定义
extern int function_mode;//1 设置功能 2 查看功能
extern int set_type;//1 设置时  2 设置分的十位  3 设置分的个位 4 完成设置

extern int look_type;//1 查看时  2 查看分的十位  3 查看分的个位

extern int h,m,s;//记录当前时钟数 初始化时钟为  8：29：00
extern int c_h,c_m,c_s;//记录闹钟时钟数
extern int c_m_gw,c_m_sw;//记录分个位 十位

extern int on_time;//0 时间未到 1 时间到

//函数声明
void led_Stopwatch(void);
void led_show(unsigned int a);
void motor(void);
	
extern char flag;


#endif
