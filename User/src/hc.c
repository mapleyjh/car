#include "hc.h"

u32 tim_count;

void HC_init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure; //GPIO��ʼ���ṹ�� int char 

	/* 1��GPIOG Peripheral clock enable   --- ʱ��ʹ��*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
	//�ṹ��  ö��  ������
	 /*2�� Configure PG6 and PG8 in output pushpull mode --��ʼ������*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 ;  //���ź�ȷ��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //����ģʽ ���� ���  ģ��  ����
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���ģʽ  ����  ��©���    ---- ������ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //�����ٶ�
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; // nopull ��������   ��������  ��ǿ��������   ---  �������ģʽ
	
	GPIO_Init(GPIOE, &GPIO_InitStructure);  //��ʼ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ;  //���ź�ȷ��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; //����ģʽ ���� ���  ģ��  ����
	
	GPIO_Init(GPIOE, &GPIO_InitStructure);  //��ʼ��
	
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
		while(ECHO == 0);//�ȴ������źŴ���  ECHO��Ϊ��
		TIM_Cmd(TIM4, ENABLE);	//������ʱ������ߵ�ƽ����ʱ��
		while(ECHO == 1); //�ȴ����ű�Ϊ�͵�ƽ
		TIM_Cmd(TIM4, DISABLE);	//�رն�ʱ����ʱ
		
		//����ʱ��Ͳ�þ���
		tim_ms = tim_count/1000.0;
		tim_count = 0;  //���㣬��ֹ���������
	
		distan = 17*tim_ms;
		
		return distan;
}



