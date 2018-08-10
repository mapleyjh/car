#include "motor.h"

//����ӿڳ�ʼ����GPIOC6789
void MOTORGPIO_Pin6789_init(void)
{
		GPIO_InitTypeDef  GPIO_InitStructure; //GPIO��ʼ���ṹ�� int char 

		/* 1��GPIOG Peripheral clock enable   --- ʱ��ʹ��*/
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
		
		//�ṹ��  ö��  ������
		 /*2�� Configure PG6 and PG8 in output pushpull mode --��ʼ������*/
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;  //���ź�ȷ��
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; //����ģʽ ����
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���ģʽ  ����  ��©���
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //�����ٶ�
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //��������  ��ǿ��������
		GPIO_Init(GPIOC, &GPIO_InitStructure);  //��ʼ��
	
		//3����GPIO���ӵ����ŵĶ�ʱ������
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM3);
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM3);
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_TIM3);
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_TIM3);

	
}
