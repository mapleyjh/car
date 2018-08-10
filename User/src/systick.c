#include "systick.h"

u8 	my_us = 0;
u16 my_ms = 0;

//初始化滴答定时器
void Systick_Init(void)
{
	//得到的Systick时钟 21MHZ
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); 
	my_us = 168/8;        //21
	my_ms = 21000;
}

//微秒延时,nms最大值:798.915
void delay_us(u32 nus)
{
	u32 temp = 0;
	//往自动重装载除值寄存器写入延时nus  SysTick->LOAD最大值0xFFFFFF
	SysTick->LOAD = nus*my_us;
	SysTick->VAL  = 0x00;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; //开启计数
	do
	{
		//读控制寄存器
		temp = SysTick->CTRL;
	}while(!(temp & (1<<16)));
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; //关闭计数
	SysTick->VAL  = 0x00;
}

//毫秒延时,nus最大值，nus最大值798915
void delay_ms(u32 nms)
{
	u32 temp = 0;
	//往自动重装载除值寄存器写入延时nus  SysTick->LOAD最大值0xFFFFFF
	SysTick->LOAD = nms*my_ms;
	SysTick->VAL  = 0x00;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; //开启计数
	do
	{
		//读控制寄存器
		temp = SysTick->CTRL;
	}while(!(temp & (1<<16)));
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; //关闭计数
	SysTick->VAL  = 0x00;

}

//秒延时
void delay_s(u32 ns)
{
	for(; ns>0; ns--)
	{
		delay_ms(500);
		delay_ms(500);
	}
}
