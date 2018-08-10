#include "pwm.h"

void GPIO_PF9init(void)
{
		GPIO_InitTypeDef  GPIO_InitStructure; //GPIO初始化结构体 int char 

		/* 1、GPIOG Peripheral clock enable   --- 时钟使能*/
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
		
		//结构体  枚举  共用体
		 /*2、 Configure PG6 and PG8 in output pushpull mode --初始化配置*/
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;  //引脚号确定
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; //引脚模式 复用
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //输出模式  推挽  开漏输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //引脚速度
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //有无上拉  增强驱动能力
		GPIO_Init(GPIOF, &GPIO_InitStructure);  //初始化
	
		//3、将GPIO连接到引脚的定时器复用
		GPIO_PinAFConfig(GPIOF, GPIO_PinSource9, GPIO_AF_TIM14);

	
}


void pwm_init(void)
{
		TIM_OCInitTypeDef  TIM_OCInitStructure;
		
		//1、初始化IO口
		//GPIO_PF9init();
		MOTORGPIO_Pin6789_init();
	
	  //2、初始化定时器
		//tim14_init();
		tim3_init();
	
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;  //PWM输出模式  1   2
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // 对定时器通道的输出使能
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low ; //输出极性  LOW：低电平有效   HIGh：高电平有效

		TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //调用初始化函数  
		TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //调用初始化函数  
		TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //调用初始化函数  
		TIM_OC4Init(TIM3, &TIM_OCInitStructure);  //调用初始化函数  
	
		//ARR  CCR
	    //3、使能定时器预装载值
		//TIM_ARRPreloadConfig(TIM14, ENABLE);
		TIM_ARRPreloadConfig(TIM3, ENABLE);
		//4、使能CCR比较值的更新
		TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
		TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
		TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
		TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);


}


void GPIO_PF8init(void)
{
		GPIO_InitTypeDef  GPIO_InitStructure; //GPIO初始化结构体 int char 

		/* 1、GPIOG Peripheral clock enable   --- 时钟使能*/
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
		
		//结构体  枚举  共用体
		 /*2、 Configure PG6 and PG8 in output pushpull mode --初始化配置*/
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;  //引脚号确定
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; //引脚模式 复用
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //输出模式  推挽  开漏输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //引脚速度
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //有无上拉  增强驱动能力
		GPIO_Init(GPIOF, &GPIO_InitStructure);  //初始化
	
		//3、将GPIO连接到引脚的定时器复用
		GPIO_PinAFConfig(GPIOF, GPIO_PinSource8, GPIO_AF_TIM14);

	
}


void tim13_init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	//1、初始化定时器时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13, ENABLE);

	//2、定时器初始化
	TIM_TimeBaseStructure.TIM_Period = 1000;	//分频值 给到84Mhz   == 10000hz  100us/脉冲  f = 1/T ARR
	TIM_TimeBaseStructure.TIM_Prescaler = 84-1; //设定自动重装载值10ms  定时时间的设定 100
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//设定定时器时钟的分频因子  不分频/1
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//配置模式 递增

	TIM_TimeBaseInit(TIM13, &TIM_TimeBaseStructure);
	
   /*3、开启定时器 TIM1 counter enable */
   TIM_Cmd(TIM13, ENABLE);


}


void tim13_pwm_init(void)
{
		TIM_OCInitTypeDef  TIM_OCInitStructure;
		
		//1、初始化IO口
		GPIO_PF8init();
	
	  //2、初始化定时器
		tim13_init();
	
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;  //PWM输出模式  1   2
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // 对定时器通道的输出使能
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low ; //输出极性  LOW：低电平有效   HIGh：高电平有效

		TIM_OC1Init(TIM13, &TIM_OCInitStructure);  //调用初始化函数  
	
		//ARR  CCR
	    //3、使能定时器预装载值
	    TIM_ARRPreloadConfig(TIM13, ENABLE);
	
		//4、使能CCR比较值的更新
		TIM_OC1PreloadConfig(TIM13, TIM_OCPreload_Enable);

}


