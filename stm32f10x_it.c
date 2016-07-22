/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTI
  
  AL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"                  // Device header
#include "stm32f10x_it.h"
#include "bsp_led.h" 
#include "stm32f10x_exti.h"
#include <RTL.h>  
#include <stdio.h>



#define	digitalHi(p,i)			{p->BSRR=i;}			//设置为高电平		
#define digitalLo(p,i)			{p->BRR=i;}				//输出低电平
#define digitalToggle(p,i)		{p->ODR ^=i;}			//输出反转状态


/* 定义控制IO的宏 */
#define GPIOA_Pin_0_TOGGLE		digitalToggle(GPIOA,GPIO_Pin_0)
#define GPIOA_Pin_2_TOGGLE		digitalToggle(GPIOA,GPIO_Pin_2)
#define GPIOB_Pin_7_TOGGLE		digitalToggle(GPIOB,GPIO_Pin_7)
#define GPIOA_Pin_3_TOGGLE		digitalToggle(GPIOA,GPIO_Pin_3)
#define LED1_OFF		digitalHi(GPIOB,GPIO_Pin_0)
#define LED1_ON			digitalLo(GPIOB,GPIO_Pin_0)

#define LED2_TOGGLE		digitalToggle(GPIOF,GPIO_Pin_7)
#define LED2_OFF		digitalHi(GPIOF,GPIO_Pin_7)
#define LED2_ON			digitalLo(GPIOF,GPIO_Pin_7)

#define LED3_TOGGLE		digitalToggle(GPIOF,GPIO_Pin_8)
#define LED3_OFF		digitalHi(GPIOF,GPIO_Pin_8)
#define LED3_ON			digitalLo(GPIOF,GPIO_Pin_8)


extern volatile u32 count;
extern	OS_TID t_StepAdd;
/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
// void SVC_Handler(void)
// {
// }

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
// void PendSV_Handler(void)
// {
//}
extern int StepCount,StepCount1;
extern volatile int    moto_running, m_status ;
extern OS_TID	t_StepMotor;   	            //步进电机任务
extern	int Count,Speed,Speed_L;
extern  int waitEvt;
extern	int r1,r3,r4;
extern	int r2;
void f(int Vt,int a,int d,int S)		//	总脉冲数=S+r2
{ 
	int pulse;
	int t1;
	t1=(Vt*10-500)/a;								//加速要走的步数
	if(	(StepCount<t1)	)               //加速阶段，分t1级加速
	{

		pulse=1000000/(500+r1);
		TIM2->ARR=pulse;
	//	TIM4->ARR=pulse;
		r1+=a;
	}                        
	else {
		if(waitEvt==1){
			waitEvt  = 0;
			isr_evt_set(0x0001,t_StepMotor);	
		}
		if(S>0){
			if(StepCount>=2*S){
				waitEvt  = 0;
				isr_evt_set(0x0010,t_StepMotor);	
				moto_running = 0;
				m_status = 0;
			}
			else if(StepCount>=2*(S-r2))                            //减速阶段，走完S步后开始减速，分t2-1级减速
			{
				if(r1>500){
					pulse=1000000/(500+r1);
					TIM2->ARR=pulse;
			//		TIM4->ARR=pulse;
					r1-=a;
				}
			}
		}
 
	}
}
void t(int Vt,int a,int d,int S)		//	总脉冲数=S+r2
{ 
	int pulse;
	int t1;
	t1=(Vt*10-500)/a;								//加速要走的步数
	if(	(StepCount1<t1)	)               //加速阶段，分t1级加速
	{

		pulse=1000000/(500+r3);
		//TIM2->ARR=pulse;
		TIM4->ARR=pulse;
		r3+=a;
	}                        
	else {
		if(waitEvt==1){
			waitEvt  = 0;
			isr_evt_set(0x0001,t_StepMotor);	
		}
		if(S>0){
			if(StepCount1>=2*S){
				waitEvt  = 0;
				isr_evt_set(0x0010,t_StepMotor);	
				moto_running = 0;
				m_status = 0;
			}
			else if(StepCount1>=2*(S-r4))                            //减速阶段，走完S步后开始减速，分t2-1级减速
			{
				if(r3>500){
					pulse=1000000/(500+31);
			//		TIM2->ARR=pulse;
					TIM4->ARR=pulse;
					r3-=a;
				}
			}
		}
 
	}
}
	
void TIM2_IRQHandler(void)				//TIM2用于产生方波
{
	if(moto_running==1){
		
		if ( TIM_GetITStatus(TIM2, TIM_IT_Update)!= RESET)
		{
			//TIM2->SR=0;
			GPIOA_Pin_2_TOGGLE;//翻转
		//	GPIOB_Pin_7_TOGGLE;
			if(StepCount >= ((((Speed/5)*10) - 500)/10))
				;
			else
				StepCount=StepCount+1;
			f((Speed/5),10,10,Count);
// 			count++;
// 			if(count==400)																									//步距角为1.8度，则200个脉冲为一圈
// 			{
// 					
// 				isr_evt_set(0x0100,t_StepAdd);															//接收400次中断为200个方波	
// 			}	
		}
	}	
	TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update); 	
}
void TIM4_IRQHandler(void)   //TIM4中断
{
	if(moto_running==1){
		
		if ( TIM_GetITStatus(TIM4, TIM_IT_Update)!= RESET)
		{
			//TIM2->SR=0;
		//	GPIOA_Pin_2_TOGGLE;//翻转
			GPIOB_Pin_7_TOGGLE;
			if(StepCount1 >= ((((Speed/5)*10) - 500)/10))
				;
			else
				StepCount1=StepCount1+1;
			t((Speed_L/5),10,10,Count);
// 			count++;
// 			if(count==400)																									//步距角为1.8度，则200个脉冲为一圈
// 			{
// 					
// 				isr_evt_set(0x0100,t_StepAdd);															//接收400次中断为200个方波	
// 			}	
		}
	}	
	TIM_ClearITPendingBit(TIM4 , TIM_FLAG_Update);
}

void USART1_IRQHandler(void)
{
	u32 a;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		a=0x01;
		a= USART_ReceiveData(USART1);
		//a=0x01;
		printf( "%d", a );
		if(a==1)
		{
			count=count+100;
			GPIO_ResetBits(GPIOA,GPIO_Pin_3);
			m_status=1;
			
		}
		if(a==2)
		{
			count=count+600;
			GPIO_ResetBits(GPIOA,GPIO_Pin_3);
			m_status=11;
			
		}
		if(a==170)
		{
			count=count+1800;
			GPIO_ResetBits(GPIOA,GPIO_Pin_3);
			m_status=111;
			
		}
		if(a==3)
		{
			count=count-100;
			GPIO_SetBits(GPIOA,GPIO_Pin_3);
			m_status=1;
		}
		if(a==4)
		{
			count=count-600;
			GPIO_SetBits(GPIOA,GPIO_Pin_3);
			m_status=11;
		}
		if(a==255)
		{
			if(count<0)
			{
				count=-count;
				GPIO_ResetBits(GPIOA,GPIO_Pin_3);
				Count=count;
				m_status=22;
			}
			else if(count==0)
			{
				m_status=0;
			}
			else
			{
				GPIO_SetBits(GPIOA,GPIO_Pin_3);
				Count=count;
				m_status=22;
				
			}
		}
	}
	 USART_ClearFlag(USART1, USART_IT_RXNE);
	
}
/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
// void SysTick_Handler(void)
// {
//}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
