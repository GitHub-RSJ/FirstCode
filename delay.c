#include"delay.h"

//���������㽭��ѧ���������Ӿ���
//��������:2015.06.06���� ������Ƭ���
//��˾������о�����ӿƼ����޹�˾
//�汾��V1.1
//��Ȩ���У�����ؾ���
//Copyright(C) ������о�����ӿƼ����޹�˾ 2015-2025
//All rights reserved

void  Delay(__IO u32 count)
{
	for(; count !=0; count--);
}

static __IO uint32_t TimingDelay;
/* Private function prototypes 
-----------------------------------------------*/
/*---------------------------------
��������ms��ʱ���� 
�� ��������1��Ϊ1ms��1000��Ϊ1s��ֻ�м�
us����
-----------------------------------*/
void Delayms(__IO uint32_t nTime) 
	{ 
		while(SysTick_Config(SystemCoreClock/1000)); 
		TimingDelay = nTime;
		while(TimingDelay != 0);
		SysTick->CTRL=0x00; //�رռ����� 
		SysTick->VAL =0X00; //��ռ����� 
	}
/*---------------------------------
��������us��ʱ���� 
�� ��������1��Ϊ1us��1000��Ϊ1ms��ֻ�м�
us����
-----------------------------------*/
void Delayus(__IO uint32_t nTime)
{ 
	while(SysTick_Config(SystemCoreClock/1000000)); 
	TimingDelay = nTime;
	while(TimingDelay != 0);
	SysTick->CTRL=0x00; //�رռ����� 
	SysTick->VAL =0X00; //��ռ����� 
}
/*---------------------------------
����������ʱ�������� 
�� ���� 
-----------------------------------*/
void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{ 
		TimingDelay--;
	}
}
/*---------------------------------
��������systick���жϺ��� 
�� ��������1��Ϊ1us��1000��Ϊ1ms��ֻ�м�
us����
-----------------------------------*/
// void SysTick_Handler(void)
// {
// TimingDelay_Decrement();
// }
/*---------------------------------
����������ʱ������ʽ��delaynus����, 
�� ��������1��Ϊ1us��1000��Ϊ1ms��
-----------------------------------*/
void delay_nus(unsigned long n)
{
	unsigned long j;
	while(n--)
	{
	j=12;
	while(j--);
}
}
/*---------------------------------
����������ʱ������ʽ��delaynms����, 
�� ��������1��Ϊ1ms��1000��Ϊ1s��
-----------------------------------*/
void delay_nms(unsigned long n)
{
	while(n--)
	delay_nus(1030);
}
