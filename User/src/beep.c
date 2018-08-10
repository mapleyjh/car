#include "beep.h"

//蜂鸣器初始化
void beep_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	/* 1、GPIOG Peripheral clock enable   --- 时钟使能*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	
	//结构体  枚举  共用体
	 /*2、 Configure PG6 and PG8 in output pushpull mode --初始化配置*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;  //引脚号确定,GPIOF8
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //引脚模式 输入 输出  模拟  复用
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //输出模式  推挽  开漏输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //引脚速度
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //有无上拉  增强驱动能力
	
	GPIO_Init(GPIOF, &GPIO_InitStructure);  //初始化
	
	GPIO_ResetBits(GPIOF,GPIO_Pin_8);

}

