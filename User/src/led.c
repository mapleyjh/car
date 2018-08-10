#include "led.h"


//��LED���ų�ʼ��
void led_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	/* 1��GPIOG Peripheral clock enable   --- ʱ��ʹ��*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
	//�ṹ��  ö��  ������
	 /*2�� Configure PG6 and PG8 in output pushpull mode --��ʼ������*/
	//��ʼ������9,10,13,14,��ӦGPIOF9,GPIOF10,GPIOE13,GPIOE14
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9| GPIO_Pin_10| GPIO_Pin_13| GPIO_Pin_14;  //���ź�ȷ��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //����ģʽ ���� ���  ģ��  ����
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���ģʽ  ����  ��©���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //�����ٶ�
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //��������  ��ǿ��������
	
	
	GPIO_Init(GPIOF, &GPIO_InitStructure);  //��ʼ��
	GPIO_Init(GPIOE, &GPIO_InitStructure);  //��ʼ��
	
	//��ʼ״̬���ó�ȫ��
	PFout(9) = 1;
	PFout (10) =1 ;
	PEout(13) = 1;
	PEout(14) =1;

}




