#include "tim.h"
#include "hc.h"

//定时器4初始化
void tim4_init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	
	
	//1、初始化定时器时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	//2、定时器初始化
	TIM_TimeBaseStructure.TIM_Period = 1;	//分频值 给到84Mhz   == 10000hz  100us/脉冲  f = 1/T ARR
	TIM_TimeBaseStructure.TIM_Prescaler = 84-1; //设定自动重装载值10ms  定时时间的设定 100
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//设定定时器时钟的分频因子  不分频/1
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//配置模式 递增

	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	//3、定时器中断更新
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	
	//4、中断向量控制器初始化
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;   //中断源
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;  //抢占优先级  优先级高可以实现中断嵌套 0~15  越小优先级越高
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;    //响应优先级  0~
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//5、中断优先级分组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	/*6、开启定时器 TIM1 counter enable */
	TIM_Cmd(TIM4, DISABLE);
	 
}


//定时器中断函数
void TIM4_IRQHandler(void)
{
		tim_count++;
		TIM_ClearFlag(TIM4,TIM_FLAG_Update);//清除中断更新标志	
}


//定时器3初始化
void tim3_init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	//1、初始化定时器时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	//2、定时器初始化
	TIM_TimeBaseStructure.TIM_Period = 1000;	//分频值 给到84Mhz   == 10000hz  100us/脉冲  f = 1/T ARR
	TIM_TimeBaseStructure.TIM_Prescaler = 84-1; //设定自动重装载值10ms  定时时间的设定 100
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//设定定时器时钟的分频因子  不分频/1
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//配置模式 递增

	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	 /*3、开启定时器 TIM1 counter enable */
	 TIM_Cmd(TIM3, ENABLE);


}

//定时器14初始化
void tim14_init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	
	//1、初始化定时器时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);

	//2、定时器初始化
	TIM_TimeBaseStructure.TIM_Period = 1000;	//分频值 给到84Mhz   == 10000hz  100us/脉冲  f = 1/T ARR
	TIM_TimeBaseStructure.TIM_Prescaler = 84-1; //设定自动重装载值10ms  定时时间的设定 100
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//设定定时器时钟的分频因子  不分频/1
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//配置模式 递增

	TIM_TimeBaseInit(TIM14, &TIM_TimeBaseStructure);
	
	//3、定时器中断更新
	TIM_ITConfig(TIM14, TIM_IT_Update, ENABLE);
	
	//4、中断向量控制器初始化
	NVIC_InitStructure.NVIC_IRQChannel = TIM8_TRG_COM_TIM14_IRQn;   //中断源
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;  //抢占优先级  优先级高可以实现中断嵌套 0~15  越小优先级越高
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;    //响应优先级  0~
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//5、中断优先级分组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
   /*6、开启定时器 TIM1 counter enable */
   TIM_Cmd(TIM14, ENABLE);


}

void TIM8_TRG_COM_TIM14_IRQHandler(void)
{
	s++;
	if(s==60)
	{	
		m++;
		s=0;
		if(m==60)
		{
			h++;
			m=0;
			if(h==12)
			{
				h=0;
			}
		}
	}
	
	c_m=c_m_sw*10+c_m_gw; //处理设置值  
	if((h==c_h) && (m==c_m) && (s==c_s))
	{
		on_time=1;
		
	}
	
	TIM_ClearFlag(TIM14,TIM_FLAG_Update);//清除中断更新标志位
}









