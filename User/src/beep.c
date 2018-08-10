#include "beep.h"

//��������ʼ��
void beep_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	/* 1��GPIOG Peripheral clock enable   --- ʱ��ʹ��*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	
	//�ṹ��  ö��  ������
	 /*2�� Configure PG6 and PG8 in output pushpull mode --��ʼ������*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;  //���ź�ȷ��,GPIOF8
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //����ģʽ ���� ���  ģ��  ����
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���ģʽ  ����  ��©���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //�����ٶ�
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //��������  ��ǿ��������
	
	GPIO_Init(GPIOF, &GPIO_InitStructure);  //��ʼ��
	
	GPIO_ResetBits(GPIOF,GPIO_Pin_8);

}

