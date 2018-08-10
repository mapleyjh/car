#include "function.h"

int function_mode=1;//1 设置功能 2 查看功能
int set_type=0;//1 设置时  2 设置分的十位  3 设置分的个位 4 完成设置

int look_type=0;//1 查看时  2 查看分的十位  3 查看分的个位

int h=8,m=30,s=0;//记录当前时钟数 初始化时钟
int c_h=0,c_m=0,c_s=0;//记录闹钟时钟数
int c_m_gw=0,c_m_sw=0;//记录分个位 十位

int on_time=0;//0 时间未到 1 时间到

float safedistan=10.0;
char flag;//全局变量默认初始值为0


void show_led(int number)
{	
	PFout(9)  = ~(( number&(1<<0) )>>0);
	PFout(10) = ~(( number&(1<<1) )>>1);
	PEout(13) = ~(( number&(1<<2) )>>2);
	PEout(14) = ~(( number&(1<<3) )>>3);
}

void function_init(void)
{
	function_mode=1;//1 设置功能 2 查看功能
	set_type=0;//1 设置时  2 设置分的十位  3 设置分的个位 4 设置完毕

	look_type=0;//1 查看时  2 查看分的十位  3 查看分的个位
	
	c_h=0;
	c_m=0;
	c_s=0;//记录闹钟时钟数
	
	c_m_gw=0;
	c_m_sw=0;//记录分个位 十位

	on_time=0;//0 时间未到 1 时间到

}



void set_clock(void)
{
	if((function_mode==1)&&(set_type==1))//设置时模式
	{
		show_led(c_h);
	}
	else if((function_mode==1)&&(set_type==2) )//设置分的十位模式
	{
		show_led((c_m_sw));
	}
	else if((function_mode==1)&&(set_type==3) )//设置分的个位模式
	{
		show_led((c_m_gw));
	}
}


void look_clock(void)
{
	if((function_mode==2)&&(look_type==1))//查看时模式
	{
		show_led(c_h);
	}
	else if((function_mode==2)&&(look_type==2) )//查看分模式十位
	{
		show_led((c_m_sw));
	}
	else if((function_mode==2)&&(look_type==3) )//设置分模式个位
	{
		show_led((c_m_gw));
	}
}

void wait_clock(void)
{
	int i;
	if( on_time==1 )//如果闹钟到了
	{
		for(i=0;i<1000;i++)
		{
			TIM_SetCompare1(TIM13, i);
		}
		for(i=1000;i>0;i--)
		{
			TIM_SetCompare1(TIM13, i);
		}
		//song();
	}
	else
	{
		TIM_SetCompare1(TIM13, 0);	
	}
}


	


void hc(void)
{
	float   distan; //局部变量名字可以相同
	delay_ms(500);
	distan = Get_distan(); //测距
	printf("distan:%f\r\n",distan);		

	if(distan<safedistan)
		{
			PFout(9)=0;
			PFout(10)=0;
			PEout(13)=0;
			PEout(14)=0;	
			
			TIM_SetCompare1( TIM3, 1000);
			TIM_SetCompare2( TIM3, 0 );
			TIM_SetCompare3( TIM3, 0);
			TIM_SetCompare4( TIM3, 1000 );
			
			delay_ms(500);
			
//			TIM_SetCompare1( TIM3, 500 );
//			TIM_SetCompare2( TIM3, 0 );
//			TIM_SetCompare3( TIM3, 500 );
//			TIM_SetCompare4( TIM3, 0 );
////			
//			delay_ms(900);
//			
			TIM_SetCompare1( TIM3, 0 );
			TIM_SetCompare2( TIM3, 0 );
			TIM_SetCompare3( TIM3, 0 );
			TIM_SetCompare4( TIM3, 0 );


		}
	else if(distan>=safedistan)
		{
			PFout(9)=1;
			PFout(10)=1;
			PEout(13)=1;
			PEout(14)=1;

		}
	
}

void motor(void)
{
	Systick_Init(); //滴答定时器初始化  主要用于延时函数 精准延时
	led_init();  //调用初始函数
	exti_key();//按键外部中断初始化  EXTI0
	pwm_init(); //PF9定时器PWM输出初始化
	beep_init();//蜂鸣器初始化
	HC_init();
	tim4_init();

	
	Uart1_init(115200);
	Uart2_init(9600);
	int j=5;
	while (1)
	{ 

		hc();	
		if(recvend == 1)
		{
			
			int i;
			i=j*100;
			if(j<=1)
				j=1;
			else if(j>10)
				j=10;
			printf("%c\r\n",recvbuf);
			recvend = 0; //进入条件立刻清零

			switch(recvbuf)
			{
				case '1'://前进
					GPIO_SetBits(GPIOF,GPIO_Pin_8);
					
					PFout(9)=0;
					PFout(10)=1;
					PEout(13)=1;
					PEout(14)=1;
				
					TIM_SetCompare1( TIM3, i );
					TIM_SetCompare2( TIM3, 0 );
					TIM_SetCompare3( TIM3, i );
					TIM_SetCompare4( TIM3, 0 );

					delay_ms(30);
					GPIO_ResetBits(GPIOF,GPIO_Pin_8);
					break;
				case '2'://后退
					GPIO_SetBits(GPIOF,GPIO_Pin_8);
					
					PFout(9)=1;
					PFout(10)=0;
					PEout(13)=1;
					PEout(14)=1;
				
					TIM_SetCompare1( TIM3, 0 );
					TIM_SetCompare2( TIM3, i );
					TIM_SetCompare3( TIM3, 0 );
					TIM_SetCompare4( TIM3, i );
					
					delay_ms(30);
					GPIO_ResetBits(GPIOF,GPIO_Pin_8);
					break;
				case '3'://右转
					GPIO_SetBits(GPIOF,GPIO_Pin_8);

					PFout(9)=1;
					PFout(10)=1;
					PEout(13)=0;
					PEout(14)=1;
				
					TIM_SetCompare1( TIM3, 1000 );
					TIM_SetCompare2( TIM3, 0 );
					TIM_SetCompare3( TIM3, i );
					TIM_SetCompare4( TIM3, 0 );								
								
					delay_ms(30);
					GPIO_ResetBits(GPIOF,GPIO_Pin_8);
					break;
				case '4'://左转
					GPIO_SetBits(GPIOF,GPIO_Pin_8);

					PFout(9)=1;
					PFout(10)=1;
					PEout(13)=1;
					PEout(14)=0;
				
					TIM_SetCompare1( TIM3, i );
					TIM_SetCompare2( TIM3, 0 );
					TIM_SetCompare3( TIM3, 1000 );
					TIM_SetCompare4( TIM3, 0 );
				
					delay_ms(30);					
					GPIO_ResetBits(GPIOF,GPIO_Pin_8);
					break;
				case '5'://停止
					GPIO_SetBits(GPIOF,GPIO_Pin_8);

					//PEout(14) = ~PEout(14);
					PFout(9)=1;
					PFout(10)=1;
					PEout(13)=1;
					PEout(14)=1;
							
					TIM_SetCompare1( TIM3, 0 );
					TIM_SetCompare2( TIM3, 0 );
					TIM_SetCompare3( TIM3, 0 );
					TIM_SetCompare4( TIM3, 0 );
				
					delay_ms(30);
					GPIO_ResetBits(GPIOF,GPIO_Pin_8);
					break;
				case '6'://原地右转
					GPIO_SetBits(GPIOF,GPIO_Pin_8);

					//PEout(14) = ~PEout(14);
					PFout(9)=1;
					PFout(10)=1;
					PEout(13)=1;
					PEout(14)=1;
					
				
					TIM_SetCompare1( TIM3, i );
					TIM_SetCompare2( TIM3, 0 );
					TIM_SetCompare3( TIM3, 0 );
					TIM_SetCompare4( TIM3, i );
				
					delay_ms(30);				
					GPIO_ResetBits(GPIOF,GPIO_Pin_8);
					break;
				
				case '7'://原地左转
					GPIO_SetBits(GPIOF,GPIO_Pin_8);

					//PEout(14) = ~PEout(14);
					PFout(9)=1;
					PFout(10)=1;
					PEout(13)=1;
					PEout(14)=1;
								
					TIM_SetCompare1( TIM3, 0 );
					TIM_SetCompare2( TIM3, i);
					TIM_SetCompare3( TIM3, i );
					TIM_SetCompare4( TIM3, 0 );
				
					delay_ms(30);				
					GPIO_ResetBits(GPIOF,GPIO_Pin_8);
					break;
				
				case '8'://加速
					GPIO_SetBits(GPIOF,GPIO_Pin_8);
				
					j++;
				
					delay_ms(30);					
					GPIO_ResetBits(GPIOF,GPIO_Pin_8);
					
					break;
				case '9'://减速
					GPIO_SetBits(GPIOF,GPIO_Pin_8);

					j--;
				
					delay_ms(30);					
					GPIO_ResetBits(GPIOF,GPIO_Pin_8);
					break;
				
				case 'a'://右退转
					GPIO_SetBits(GPIOF,GPIO_Pin_8);

					PFout(9)=1;
					PFout(10)=1;
					PEout(13)=0;
					PEout(14)=1;
				
					TIM_SetCompare1( TIM3, 0 );
					TIM_SetCompare2( TIM3, 1000 );
					TIM_SetCompare3( TIM3, 0 );
					TIM_SetCompare4( TIM3, i );								
								
					delay_ms(30);
					GPIO_ResetBits(GPIOF,GPIO_Pin_8);
					break;
				case 'b'://左退转
					GPIO_SetBits(GPIOF,GPIO_Pin_8);

					PFout(9)=1;
					PFout(10)=1;
					PEout(13)=1;
					PEout(14)=0;
				
					TIM_SetCompare1( TIM3, 0 );
					TIM_SetCompare2( TIM3, i );
					TIM_SetCompare3( TIM3, 0 );
					TIM_SetCompare4( TIM3, 1000 );
				
					delay_ms(30);					
					GPIO_ResetBits(GPIOF,GPIO_Pin_8);
					break;

				case 'c'://全速
					GPIO_SetBits(GPIOF,GPIO_Pin_8);
				
					j=10;
				
					delay_ms(30);					
					GPIO_ResetBits(GPIOF,GPIO_Pin_8);
					
					break;
				case 'd'://初速
					GPIO_SetBits(GPIOF,GPIO_Pin_8);

					j=5;
					safedistan = 10;
				
					delay_ms(30);					
					GPIO_ResetBits(GPIOF,GPIO_Pin_8);
					break;
				
				case 'e'://闹钟设置功能开启
					GPIO_SetBits(GPIOF,GPIO_Pin_8);
					printf("now time:%d h %d min %d s",h,m,s);
					if(function_mode==1) //如果当前是设置模式
					{
						set_type++; 
						if(set_type==4)//闹钟设置完毕
						{
							function_mode=2;// 查看功能可用 
						}
					}
					
					delay_ms(30);
					GPIO_ResetBits(GPIOF,GPIO_Pin_8);
					break;
				case 'f'://设置时分秒（加值）
					GPIO_SetBits(GPIOF,GPIO_Pin_8);
					if(function_mode==1)
					{	
						if(set_type==1)//如果当前设置的是时
						{
							c_h++;
							if(c_h>12)
							{
								c_h=0;
							}
						}
						else if(set_type==2)//如果当前设置的是分的十位
						{
							c_m_sw++;
							if(c_m_sw>5)
							{
								c_m_sw=0;
							}
						}
						else if(set_type==3)//如果当前设置的是分的个位
						{
							c_m_gw++;
							if(c_m_gw>9)
							{
								c_m_gw=0;
							}
						
						}
						
					}
					set_clock();
					delay_ms(30);
					GPIO_ResetBits(GPIOF,GPIO_Pin_8);
					break;
				case 'g'://设置时分秒（减值）	
					GPIO_SetBits(GPIOF,GPIO_Pin_8);
					if(function_mode==1)
					{	
						if(set_type==1)//如果当前设置的是时
						{
							c_h--;
							if(c_h<0)
							{
								c_h=12;
							}
						}
						else if(set_type==2)//如果当前设置的是分的十位
						{
							c_m_sw--;
							if(c_m_sw<0)
							{
								c_m_sw=5;
							}
						}
						else if(set_type==3)//如果当前设置的是分的个位
						{
							c_m_gw--;
							if(c_m_gw<0)
							{
								c_m_gw=9;
							}
						
						}
						
					}
					set_clock();
					delay_ms(30);
					GPIO_ResetBits(GPIOF,GPIO_Pin_8);
					break;
				case 'h':
					GPIO_SetBits(GPIOF,GPIO_Pin_8);
					if(function_mode==2)
					{	
						look_type++;
						if(look_type>3)			
						{
							look_type=1;
						}
								
					}
					look_clock();
					delay_ms(30);
					GPIO_ResetBits(GPIOF,GPIO_Pin_8);
					break;
				case 'i':
					GPIO_SetBits(GPIOF,GPIO_Pin_8);
					function_init();
					delay_ms(30);					
					GPIO_ResetBits(GPIOF,GPIO_Pin_8);
					break;
				case 'j':
					GPIO_SetBits(GPIOF,GPIO_Pin_8);
				
					safedistan = safedistan + 10;
					if(safedistan>50)
					{
						safedistan = 50;
					}
					show_led(safedistan/10);
					delay_ms(30);					
					GPIO_ResetBits(GPIOF,GPIO_Pin_8);
					break;
				case 'k':
					GPIO_SetBits(GPIOF,GPIO_Pin_8);
				
					safedistan = safedistan - 10;
					if(safedistan<10)
					{
						safedistan = 10;
					}
					show_led(safedistan/10);
					delay_ms(30);					
					GPIO_ResetBits(GPIOF,GPIO_Pin_8);
					break;
			}
			wait_clock();
			//hc();	
		
		}
		
	}
}



