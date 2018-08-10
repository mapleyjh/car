#include "pwm.h"

void GPIO_PF9init(void)
{
		GPIO_InitTypeDef  GPIO_InitStructure; //GPIO��ʼ���ṹ�� int char 

		/* 1��GPIOG Peripheral clock enable   --- ʱ��ʹ��*/
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
		
		//�ṹ��  ö��  ������
		 /*2�� Configure PG6 and PG8 in output pushpull mode --��ʼ������*/
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;  //���ź�ȷ��
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; //����ģʽ ����
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���ģʽ  ����  ��©���
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //�����ٶ�
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //��������  ��ǿ��������
		GPIO_Init(GPIOF, &GPIO_InitStructure);  //��ʼ��
	
		//3����GPIO���ӵ����ŵĶ�ʱ������
		GPIO_PinAFConfig(GPIOF, GPIO_PinSource9, GPIO_AF_TIM14);

	
}


void pwm_init(void)
{
		TIM_OCInitTypeDef  TIM_OCInitStructure;
		
		//1����ʼ��IO��
		//GPIO_PF9init();
		MOTORGPIO_Pin6789_init();
	
	  //2����ʼ����ʱ��
		//tim14_init();
		tim3_init();
	
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;  //PWM���ģʽ  1   2
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // �Զ�ʱ��ͨ�������ʹ��
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low ; //�������  LOW���͵�ƽ��Ч   HIGh���ߵ�ƽ��Ч

		TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //���ó�ʼ������  
		TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //���ó�ʼ������  
		TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //���ó�ʼ������  
		TIM_OC4Init(TIM3, &TIM_OCInitStructure);  //���ó�ʼ������  
	
		//ARR  CCR
	    //3��ʹ�ܶ�ʱ��Ԥװ��ֵ
		//TIM_ARRPreloadConfig(TIM14, ENABLE);
		TIM_ARRPreloadConfig(TIM3, ENABLE);
		//4��ʹ��CCR�Ƚ�ֵ�ĸ���
		TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
		TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
		TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
		TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);


}


void GPIO_PF8init(void)
{
		GPIO_InitTypeDef  GPIO_InitStructure; //GPIO��ʼ���ṹ�� int char 

		/* 1��GPIOG Peripheral clock enable   --- ʱ��ʹ��*/
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
		
		//�ṹ��  ö��  ������
		 /*2�� Configure PG6 and PG8 in output pushpull mode --��ʼ������*/
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;  //���ź�ȷ��
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; //����ģʽ ����
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���ģʽ  ����  ��©���
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //�����ٶ�
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //��������  ��ǿ��������
		GPIO_Init(GPIOF, &GPIO_InitStructure);  //��ʼ��
	
		//3����GPIO���ӵ����ŵĶ�ʱ������
		GPIO_PinAFConfig(GPIOF, GPIO_PinSource8, GPIO_AF_TIM14);

	
}


void tim13_init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	//1����ʼ����ʱ��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13, ENABLE);

	//2����ʱ����ʼ��
	TIM_TimeBaseStructure.TIM_Period = 1000;	//��Ƶֵ ����84Mhz   == 10000hz  100us/����  f = 1/T ARR
	TIM_TimeBaseStructure.TIM_Prescaler = 84-1; //�趨�Զ���װ��ֵ10ms  ��ʱʱ����趨 100
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//�趨��ʱ��ʱ�ӵķ�Ƶ����  ����Ƶ/1
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//����ģʽ ����

	TIM_TimeBaseInit(TIM13, &TIM_TimeBaseStructure);
	
   /*3��������ʱ�� TIM1 counter enable */
   TIM_Cmd(TIM13, ENABLE);


}


void tim13_pwm_init(void)
{
		TIM_OCInitTypeDef  TIM_OCInitStructure;
		
		//1����ʼ��IO��
		GPIO_PF8init();
	
	  //2����ʼ����ʱ��
		tim13_init();
	
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;  //PWM���ģʽ  1   2
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // �Զ�ʱ��ͨ�������ʹ��
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low ; //�������  LOW���͵�ƽ��Ч   HIGh���ߵ�ƽ��Ч

		TIM_OC1Init(TIM13, &TIM_OCInitStructure);  //���ó�ʼ������  
	
		//ARR  CCR
	    //3��ʹ�ܶ�ʱ��Ԥװ��ֵ
	    TIM_ARRPreloadConfig(TIM13, ENABLE);
	
		//4��ʹ��CCR�Ƚ�ֵ�ĸ���
		TIM_OC1PreloadConfig(TIM13, TIM_OCPreload_Enable);

}


