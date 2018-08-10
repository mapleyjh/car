#include "function.h"

int function_mode=1;//1 ���ù��� 2 �鿴����
int set_type=0;//1 ����ʱ  2 ���÷ֵ�ʮλ  3 ���÷ֵĸ�λ 4 �������

int look_type=0;//1 �鿴ʱ  2 �鿴�ֵ�ʮλ  3 �鿴�ֵĸ�λ

int h=8,m=30,s=0;//��¼��ǰʱ���� ��ʼ��ʱ��
int c_h=0,c_m=0,c_s=0;//��¼����ʱ����
int c_m_gw=0,c_m_sw=0;//��¼�ָ�λ ʮλ

int on_time=0;//0 ʱ��δ�� 1 ʱ�䵽

float safedistan=10.0;
char flag;//ȫ�ֱ���Ĭ�ϳ�ʼֵΪ0


void show_led(int number)
{	
	PFout(9)  = ~(( number&(1<<0) )>>0);
	PFout(10) = ~(( number&(1<<1) )>>1);
	PEout(13) = ~(( number&(1<<2) )>>2);
	PEout(14) = ~(( number&(1<<3) )>>3);
}

void function_init(void)
{
	function_mode=1;//1 ���ù��� 2 �鿴����
	set_type=0;//1 ����ʱ  2 ���÷ֵ�ʮλ  3 ���÷ֵĸ�λ 4 �������

	look_type=0;//1 �鿴ʱ  2 �鿴�ֵ�ʮλ  3 �鿴�ֵĸ�λ
	
	c_h=0;
	c_m=0;
	c_s=0;//��¼����ʱ����
	
	c_m_gw=0;
	c_m_sw=0;//��¼�ָ�λ ʮλ

	on_time=0;//0 ʱ��δ�� 1 ʱ�䵽

}



void set_clock(void)
{
	if((function_mode==1)&&(set_type==1))//����ʱģʽ
	{
		show_led(c_h);
	}
	else if((function_mode==1)&&(set_type==2) )//���÷ֵ�ʮλģʽ
	{
		show_led((c_m_sw));
	}
	else if((function_mode==1)&&(set_type==3) )//���÷ֵĸ�λģʽ
	{
		show_led((c_m_gw));
	}
}


void look_clock(void)
{
	if((function_mode==2)&&(look_type==1))//�鿴ʱģʽ
	{
		show_led(c_h);
	}
	else if((function_mode==2)&&(look_type==2) )//�鿴��ģʽʮλ
	{
		show_led((c_m_sw));
	}
	else if((function_mode==2)&&(look_type==3) )//���÷�ģʽ��λ
	{
		show_led((c_m_gw));
	}
}

void wait_clock(void)
{
	int i;
	if( on_time==1 )//������ӵ���
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
	float   distan; //�ֲ��������ֿ�����ͬ
	delay_ms(500);
	distan = Get_distan(); //���
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
	Systick_Init(); //�δ�ʱ����ʼ��  ��Ҫ������ʱ���� ��׼��ʱ
	led_init();  //���ó�ʼ����
	exti_key();//�����ⲿ�жϳ�ʼ��  EXTI0
	pwm_init(); //PF9��ʱ��PWM�����ʼ��
	beep_init();//��������ʼ��
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
			recvend = 0; //����������������

			switch(recvbuf)
			{
				case '1'://ǰ��
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
				case '2'://����
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
				case '3'://��ת
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
				case '4'://��ת
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
				case '5'://ֹͣ
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
				case '6'://ԭ����ת
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
				
				case '7'://ԭ����ת
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
				
				case '8'://����
					GPIO_SetBits(GPIOF,GPIO_Pin_8);
				
					j++;
				
					delay_ms(30);					
					GPIO_ResetBits(GPIOF,GPIO_Pin_8);
					
					break;
				case '9'://����
					GPIO_SetBits(GPIOF,GPIO_Pin_8);

					j--;
				
					delay_ms(30);					
					GPIO_ResetBits(GPIOF,GPIO_Pin_8);
					break;
				
				case 'a'://����ת
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
				case 'b'://����ת
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

				case 'c'://ȫ��
					GPIO_SetBits(GPIOF,GPIO_Pin_8);
				
					j=10;
				
					delay_ms(30);					
					GPIO_ResetBits(GPIOF,GPIO_Pin_8);
					
					break;
				case 'd'://����
					GPIO_SetBits(GPIOF,GPIO_Pin_8);

					j=5;
					safedistan = 10;
				
					delay_ms(30);					
					GPIO_ResetBits(GPIOF,GPIO_Pin_8);
					break;
				
				case 'e'://�������ù��ܿ���
					GPIO_SetBits(GPIOF,GPIO_Pin_8);
					printf("now time:%d h %d min %d s",h,m,s);
					if(function_mode==1) //�����ǰ������ģʽ
					{
						set_type++; 
						if(set_type==4)//�����������
						{
							function_mode=2;// �鿴���ܿ��� 
						}
					}
					
					delay_ms(30);
					GPIO_ResetBits(GPIOF,GPIO_Pin_8);
					break;
				case 'f'://����ʱ���루��ֵ��
					GPIO_SetBits(GPIOF,GPIO_Pin_8);
					if(function_mode==1)
					{	
						if(set_type==1)//�����ǰ���õ���ʱ
						{
							c_h++;
							if(c_h>12)
							{
								c_h=0;
							}
						}
						else if(set_type==2)//�����ǰ���õ��Ƿֵ�ʮλ
						{
							c_m_sw++;
							if(c_m_sw>5)
							{
								c_m_sw=0;
							}
						}
						else if(set_type==3)//�����ǰ���õ��Ƿֵĸ�λ
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
				case 'g'://����ʱ���루��ֵ��	
					GPIO_SetBits(GPIOF,GPIO_Pin_8);
					if(function_mode==1)
					{	
						if(set_type==1)//�����ǰ���õ���ʱ
						{
							c_h--;
							if(c_h<0)
							{
								c_h=12;
							}
						}
						else if(set_type==2)//�����ǰ���õ��Ƿֵ�ʮλ
						{
							c_m_sw--;
							if(c_m_sw<0)
							{
								c_m_sw=5;
							}
						}
						else if(set_type==3)//�����ǰ���õ��Ƿֵĸ�λ
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



