#include"delay.h"

//工程用于浙江大学宁波理工电子竞赛
//创建日期:2015.06.06建立 作者那片清茶
//公司：宁波芯瑞格电子科技有限公司
//版本：V1.1
//版权所有，盗版必究。
//Copyright(C) 宁波市芯瑞格电子科技有限公司 2015-2025
//All rights reserved

void  Delay(__IO u32 count)
{
	for(; count !=0; count--);
}

static __IO uint32_t TimingDelay;
/* Private function prototypes 
-----------------------------------------------*/
/*---------------------------------
函数名：ms延时函数 
描 述：参数1即为1ms，1000即为1s；只有几
us的误差；
-----------------------------------*/
void Delayms(__IO uint32_t nTime) 
	{ 
		while(SysTick_Config(SystemCoreClock/1000)); 
		TimingDelay = nTime;
		while(TimingDelay != 0);
		SysTick->CTRL=0x00; //关闭计数器 
		SysTick->VAL =0X00; //清空计数器 
	}
/*---------------------------------
函数名：us延时函数 
描 述：参数1即为1us，1000即为1ms；只有几
us的误差；
-----------------------------------*/
void Delayus(__IO uint32_t nTime)
{ 
	while(SysTick_Config(SystemCoreClock/1000000)); 
	TimingDelay = nTime;
	while(TimingDelay != 0);
	SysTick->CTRL=0x00; //关闭计数器 
	SysTick->VAL =0X00; //清空计数器 
}
/*---------------------------------
函数名：延时辅助函数 
描 述： 
-----------------------------------*/
void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{ 
		TimingDelay--;
	}
}
/*---------------------------------
函数名：systick的中断函数 
描 述：参数1即为1us，1000即为1ms；只有几
us的误差；
-----------------------------------*/
// void SysTick_Handler(void)
// {
// TimingDelay_Decrement();
// }
/*---------------------------------
函数名：延时调整形式的delaynus函数, 
描 述：参数1即为1us，1000即为1ms；
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
函数名：延时调整形式的delaynms函数, 
描 述：参数1即为1ms，1000即为1s；
-----------------------------------*/
void delay_nms(unsigned long n)
{
	while(n--)
	delay_nus(1030);
}
