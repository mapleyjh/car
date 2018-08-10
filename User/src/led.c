#include "led.h"


//对LED引脚初始化
void led_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	/* 1、GPIOG Peripheral clock enable   --- 时钟使能*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
	//结构体  枚举  共用体
	 /*2、 Configure PG6 and PG8 in output pushpull mode --初始化配置*/
	//初始化引脚9,10,13,14,对应GPIOF9,GPIOF10,GPIOE13,GPIOE14
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9| GPIO_Pin_10| GPIO_Pin_13| GPIO_Pin_14;  //引脚号确定
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //引脚模式 输入 输出  模拟  复用
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //输出模式  推挽  开漏输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //引脚速度
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //有无上拉  增强驱动能力
	
	
	GPIO_Init(GPIOF, &GPIO_InitStructure);  //初始化
	GPIO_Init(GPIOE, &GPIO_InitStructure);  //初始化
	
	//初始状态设置成全灭
	PFout(9) = 1;
	PFout (10) =1 ;
	PEout(13) = 1;
	PEout(14) =1;

}




