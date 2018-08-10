#include "tim.h"
#include "hc.h"

//��ʱ��4��ʼ��
void tim4_init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	
	
	//1����ʼ����ʱ��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	//2����ʱ����ʼ��
	TIM_TimeBaseStructure.TIM_Period = 1;	//��Ƶֵ ����84Mhz   == 10000hz  100us/����  f = 1/T ARR
	TIM_TimeBaseStructure.TIM_Prescaler = 84-1; //�趨�Զ���װ��ֵ10ms  ��ʱʱ����趨 100
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//�趨��ʱ��ʱ�ӵķ�Ƶ����  ����Ƶ/1
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//����ģʽ ����

	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	//3����ʱ���жϸ���
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	
	//4���ж�������������ʼ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;   //�ж�Դ
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;  //��ռ���ȼ�  ���ȼ��߿���ʵ���ж�Ƕ�� 0~15  ԽС���ȼ�Խ��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;    //��Ӧ���ȼ�  0~
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//5���ж����ȼ�����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	/*6��������ʱ�� TIM1 counter enable */
	TIM_Cmd(TIM4, DISABLE);
	 
}


//��ʱ���жϺ���
void TIM4_IRQHandler(void)
{
		tim_count++;
		TIM_ClearFlag(TIM4,TIM_FLAG_Update);//����жϸ��±�־	
}


//��ʱ��3��ʼ��
void tim3_init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	//1����ʼ����ʱ��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	//2����ʱ����ʼ��
	TIM_TimeBaseStructure.TIM_Period = 1000;	//��Ƶֵ ����84Mhz   == 10000hz  100us/����  f = 1/T ARR
	TIM_TimeBaseStructure.TIM_Prescaler = 84-1; //�趨�Զ���װ��ֵ10ms  ��ʱʱ����趨 100
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//�趨��ʱ��ʱ�ӵķ�Ƶ����  ����Ƶ/1
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//����ģʽ ����

	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	 /*3��������ʱ�� TIM1 counter enable */
	 TIM_Cmd(TIM3, ENABLE);


}

//��ʱ��14��ʼ��
void tim14_init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	
	//1����ʼ����ʱ��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);

	//2����ʱ����ʼ��
	TIM_TimeBaseStructure.TIM_Period = 1000;	//��Ƶֵ ����84Mhz   == 10000hz  100us/����  f = 1/T ARR
	TIM_TimeBaseStructure.TIM_Prescaler = 84-1; //�趨�Զ���װ��ֵ10ms  ��ʱʱ����趨 100
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//�趨��ʱ��ʱ�ӵķ�Ƶ����  ����Ƶ/1
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//����ģʽ ����

	TIM_TimeBaseInit(TIM14, &TIM_TimeBaseStructure);
	
	//3����ʱ���жϸ���
	TIM_ITConfig(TIM14, TIM_IT_Update, ENABLE);
	
	//4���ж�������������ʼ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM8_TRG_COM_TIM14_IRQn;   //�ж�Դ
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;  //��ռ���ȼ�  ���ȼ��߿���ʵ���ж�Ƕ�� 0~15  ԽС���ȼ�Խ��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;    //��Ӧ���ȼ�  0~
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//5���ж����ȼ�����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
   /*6��������ʱ�� TIM1 counter enable */
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
	
	c_m=c_m_sw*10+c_m_gw; //��������ֵ  
	if((h==c_h) && (m==c_m) && (s==c_s))
	{
		on_time=1;
		
	}
	
	TIM_ClearFlag(TIM14,TIM_FLAG_Update);//����жϸ��±�־λ
}









