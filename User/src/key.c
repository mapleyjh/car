#include "key.h"

//对四个按键引脚初始化
void key_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;//GPIO初始化结构体 int char


	/* 1、GPIOG Peripheral clock enable   --- 时钟使能*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
	//结构体  枚举  共用体
	 /*2、 Configure PG6 and PG8 in output pushpull mode --初始化配置*/
	//初始化引脚0,2,3,4,对应GPIOA0,GPIOE2,GPIOE3,GPIOE4
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;  //引脚号确定,对应引脚PA0 PE2 PE3 PE4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; //引脚模式 输入 输出  模拟  复用
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //引脚速度
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //有无上拉  增强驱动能力
	

	GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化
	GPIO_Init(GPIOE, &GPIO_InitStructure);  //初始化

	
}

void exti_key(void)
{
	 //外部中断初始化结构体
	EXTI_InitTypeDef   EXTI_InitStructure; 	
	NVIC_InitTypeDef   NVIC_InitStructure;

		
	//1、时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	
	//1.5、引脚初始化为输入模式
	key_init();
	
	//2、连接中断线资源0到PA0、2到PE2、3到PE3、4到PE4
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource2);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);
		
	//3、初始化外部中断
	EXTI_InitStructure.EXTI_Line = EXTI_Line0 | EXTI_Line2 | EXTI_Line3 | EXTI_Line4;  //中断线0、2、3、4 ----对应引脚PA0 PE2 PE3 PE4
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; //中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  //触发方式  上升沿
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	//4、中断向量控制器初始化
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn | EXTI2_IRQn | EXTI3_IRQn | EXTI4_IRQn;   //中断源
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;  //抢占优先级  优先级高可以实现中断嵌套 0~15
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;    //响应优先级  0~
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	
	//5、中断优先级分组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

}



//key1中断函数
void EXTI0_IRQHandler(void)
{

	//GPIO_SetBits(GPIOF,GPIO_Pin_8);
	//delay_ms(60);
	flag = ~ flag ;
	//GPIO_ResetBits(GPIOF,GPIO_Pin_8);

	
	EXTI_ClearFlag(EXTI_Line0);//清除中断标志位，防止重复进入中断
}

//key2中断函数
void EXTI2_IRQHandler(void)
{
	GPIO_SetBits(GPIOF,GPIO_Pin_8);
	delay_ms(60);
	PFout(10) = ~PFout(10);
	GPIO_ResetBits(GPIOF,GPIO_Pin_8);

	
	EXTI_ClearFlag(EXTI_Line2);//清除中断标志位，防止重复进入中断
}

//key3中断函数
void EXTI3_IRQHandler(void)
{
	GPIO_SetBits(GPIOF,GPIO_Pin_8);
	delay_ms(60);
	PEout(13) = ~PEout(13);
	GPIO_ResetBits(GPIOF,GPIO_Pin_8);

	
	EXTI_ClearFlag(EXTI_Line3);//清除中断标志位，防止重复进入中断
}

//key4中断函数
void EXTI4_IRQHandler(void)
{
	GPIO_SetBits(GPIOF,GPIO_Pin_8);
	delay_ms(30);
	PEout(14) = ~PEout(14);
	GPIO_ResetBits(GPIOF,GPIO_Pin_8);

	
	EXTI_ClearFlag(EXTI_Line4);//清除中断标志位，防止重复进入中断
}
