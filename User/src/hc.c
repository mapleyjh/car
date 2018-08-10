#include "hc.h"

u32 tim_count;

void HC_init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure; //GPIO初始化结构体 int char 

	/* 1、GPIOG Peripheral clock enable   --- 时钟使能*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
	//结构体  枚举  共用体
	 /*2、 Configure PG6 and PG8 in output pushpull mode --初始化配置*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 ;  //引脚号确定
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //引脚模式 输入 输出  模拟  复用
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //输出模式  推挽  开漏输出    ---- 针对输出模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //引脚速度
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; // nopull 浮空输入   有无上拉  增强驱动能力   ---  针对输入模式
	
	GPIO_Init(GPIOE, &GPIO_InitStructure);  //初始化
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ;  //引脚号确定
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; //引脚模式 输入 输出  模拟  复用
	
	GPIO_Init(GPIOE, &GPIO_InitStructure);  //初始化
	
	TRIG = 0;
	ECHO =0;
}


void hc_start(void)
{
	TRIG = 1;
	delay_us(13);
	TRIG = 0;
}


float  Get_distan(void)
{
	
		float  tim_ms;
		float  distan;
		hc_start();
		while(ECHO == 0);//等待回响信号触发  ECHO变为高
		TIM_Cmd(TIM4, ENABLE);	//开启定时器计算高电平持续时间
		while(ECHO == 1); //等待引脚变为低电平
		TIM_Cmd(TIM4, DISABLE);	//关闭定时器计时
		
		//处理时间和测得距离
		tim_ms = tim_count/1000.0;
		tim_count = 0;  //清零，防止计数的溢出
	
		distan = 17*tim_ms;
		
		return distan;
}



