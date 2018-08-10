#include "motor.h"

//电机接口初始化，GPIOC6789
void MOTORGPIO_Pin6789_init(void)
{
		GPIO_InitTypeDef  GPIO_InitStructure; //GPIO初始化结构体 int char 

		/* 1、GPIOG Peripheral clock enable   --- 时钟使能*/
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
		
		//结构体  枚举  共用体
		 /*2、 Configure PG6 and PG8 in output pushpull mode --初始化配置*/
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;  //引脚号确定
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; //引脚模式 复用
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //输出模式  推挽  开漏输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //引脚速度
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //有无上拉  增强驱动能力
		GPIO_Init(GPIOC, &GPIO_InitStructure);  //初始化
	
		//3、将GPIO连接到引脚的定时器复用
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM3);
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM3);
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_TIM3);
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_TIM3);

	
}
