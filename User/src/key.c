#include "key.h"

//���ĸ��������ų�ʼ��
void key_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;//GPIO��ʼ���ṹ�� int char


	/* 1��GPIOG Peripheral clock enable   --- ʱ��ʹ��*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
	//�ṹ��  ö��  ������
	 /*2�� Configure PG6 and PG8 in output pushpull mode --��ʼ������*/
	//��ʼ������0,2,3,4,��ӦGPIOA0,GPIOE2,GPIOE3,GPIOE4
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;  //���ź�ȷ��,��Ӧ����PA0 PE2 PE3 PE4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; //����ģʽ ���� ���  ģ��  ����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //�����ٶ�
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //��������  ��ǿ��������
	

	GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��
	GPIO_Init(GPIOE, &GPIO_InitStructure);  //��ʼ��

	
}

void exti_key(void)
{
	 //�ⲿ�жϳ�ʼ���ṹ��
	EXTI_InitTypeDef   EXTI_InitStructure; 	
	NVIC_InitTypeDef   NVIC_InitStructure;

		
	//1��ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	
	//1.5�����ų�ʼ��Ϊ����ģʽ
	key_init();
	
	//2�������ж�����Դ0��PA0��2��PE2��3��PE3��4��PE4
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource2);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);
		
	//3����ʼ���ⲿ�ж�
	EXTI_InitStructure.EXTI_Line = EXTI_Line0 | EXTI_Line2 | EXTI_Line3 | EXTI_Line4;  //�ж���0��2��3��4 ----��Ӧ����PA0 PE2 PE3 PE4
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; //�ж�ģʽ
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  //������ʽ  ������
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	//4���ж�������������ʼ��
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn | EXTI2_IRQn | EXTI3_IRQn | EXTI4_IRQn;   //�ж�Դ
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;  //��ռ���ȼ�  ���ȼ��߿���ʵ���ж�Ƕ�� 0~15
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;    //��Ӧ���ȼ�  0~
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	
	//5���ж����ȼ�����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

}



//key1�жϺ���
void EXTI0_IRQHandler(void)
{

	//GPIO_SetBits(GPIOF,GPIO_Pin_8);
	//delay_ms(60);
	flag = ~ flag ;
	//GPIO_ResetBits(GPIOF,GPIO_Pin_8);

	
	EXTI_ClearFlag(EXTI_Line0);//����жϱ�־λ����ֹ�ظ������ж�
}

//key2�жϺ���
void EXTI2_IRQHandler(void)
{
	GPIO_SetBits(GPIOF,GPIO_Pin_8);
	delay_ms(60);
	PFout(10) = ~PFout(10);
	GPIO_ResetBits(GPIOF,GPIO_Pin_8);

	
	EXTI_ClearFlag(EXTI_Line2);//����жϱ�־λ����ֹ�ظ������ж�
}

//key3�жϺ���
void EXTI3_IRQHandler(void)
{
	GPIO_SetBits(GPIOF,GPIO_Pin_8);
	delay_ms(60);
	PEout(13) = ~PEout(13);
	GPIO_ResetBits(GPIOF,GPIO_Pin_8);

	
	EXTI_ClearFlag(EXTI_Line3);//����жϱ�־λ����ֹ�ظ������ж�
}

//key4�жϺ���
void EXTI4_IRQHandler(void)
{
	GPIO_SetBits(GPIOF,GPIO_Pin_8);
	delay_ms(30);
	PEout(14) = ~PEout(14);
	GPIO_ResetBits(GPIOF,GPIO_Pin_8);

	
	EXTI_ClearFlag(EXTI_Line4);//����жϱ�־λ����ֹ�ظ������ж�
}
