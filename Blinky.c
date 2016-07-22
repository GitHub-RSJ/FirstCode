/*  电机控制程序

A3，A4,C6：方向，使能，脉冲

时钟节拍0.1MS
*/


#include <stm32f10x.h>
#include <RTL.h>                      /* RTX kernel functions & defines      */
#include "bsp_TiMbase.h"
#include "stm32f10x_it.h"
#include "delay.h"
#include "bsp_usart1.h"


#include "BSP_LED.h"
#include "BSP_LCD.h"

#define MAX_STEPMOTO_SPEED 900	//RPM
volatile u32    count= 0;        		//记步变量，在中断服务函数中计数		
volatile int    m_status = 0 ;  			//步进电机当前工作状态
																		

volatile int    moto_running  = 0 ;
int StepCount=0;
int StepCount1=0;
int Count;
int waitEvt;
int Speed=500;					//默认速度500hz
int Speed_L=500;
int r1,r3,r4;
int r2;
char *a;
char *b;
volatile int pwm; 
OS_SEM sem1,sem2,sem3,sem4;

OS_TID	t_StepMotor;   	            //步进电机任务
OS_TID  t_Key;					            //按键任务
OS_TID  t_StepAdd;			            //步进电机计步任务
OS_TID  t_LCD;					            //LCD显示任务
OS_TID  t_PWM;											//PWM输出任务
OS_TID  t_Ultrasonic;								//超声波测距任务


//步进电机控制任务
__task void StepMotor (void)                   //A3，A4,C6：方向，使能，脉冲
{	
//	int timecount;																
	//os_itv_set (5);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 , ENABLE);
	Speed=8800;
	Speed_L=8800;
	while(1)
	{
//		if(Count < 100000)
//			Count = 1000000;
		//os_itv_wait ();
		
		switch  (m_status)
		{
			case 0: // 0 电机静止中
                Motor_A_DIS;
                Motor_B_DIS;
				break;			
				
			case 1:// 1 电机启动开始
				// 先置低速频率
				TIM2->ARR=((SystemCoreClock / 48 / 1000  ) - 1);
			  TIM4->ARR=((SystemCoreClock / 48 / 1000  ) - 1);
				
				Count =100000;
				r1=0;
				r2=100;	//r2减速提前脉冲数量
			r3=0;
				r4=100;	//r2减速提前脉冲数量
				StepCount=0;
			StepCount1=0;
				moto_running  = 1 ;
				m_status = 2;
				break;			
			case 2:// 2 电机启动加速中
				waitEvt = 1;
				os_evt_wait_or(0x0001,0xFFFF);
				m_status = 3;
				break;
			case 3:// 3 电机匀速运行		
				break;

			case 11: 	
				TIM2->ARR=((SystemCoreClock / 48 / 1000  ) - 1);
				Speed=1000;
				Count =600;
				r1=0;
				r2=100;	//r2减速提前脉冲数量
				StepCount=0;
				moto_running  = 1 ;
				m_status = 2;
				break;				
			case 111: 
				TIM2->ARR=((SystemCoreClock / 48 / 1000  ) - 1);
				Speed=1000;
				Count =1800;
				r1=0;
				r2=100;	//r2减速提前脉冲数量
				StepCount=0;
				moto_running  = 1 ;
				m_status = 2;
				break;
			case 22: 
				count=0;
				TIM2->ARR=((SystemCoreClock / 48 / 1000  ) - 1);
				Speed=1000;
				r1=0;
				r2=100;	//r2减速提前脉冲数量
				StepCount=0;
				moto_running  = 1 ;
				m_status = 2;
				break;
			
			}
		os_dly_wait(1);
	}
}
	
__task void LCD(void)
{
    BSP_LCD_Init();
    SHOW_BMP();
	while(1)
	{

	}
}

__task void PWM (void)  
{
		while(1)
		{
			TIM3->CCR3=800;													 //TIM3 PWM通道3
			pwm=TIM3->CCR3/10;
			os_dly_wait(1);
		}
		
}


__task void Key (void) 
{
	Key_GPIO_Config();
    while(1)
    {
//        if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)==0)        //启动
//        {
//            os_dly_wait  (100); 
//            if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)==0)  
//            {
//                if(m_status==0)
//                {
//                    m_status = 1;
//                }
//            }
//        }
        if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)==0)        //启动
        { 
            os_dly_wait  (100); 
            if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)==0)  
            {              
                if(m_status==0)
                {
                    Motor_A_EN;
                    Motor_B_EN;
                    m_status = 1;
                }
            }
        }
        
//        if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12)==0)        //启动
//        {
//            os_dly_wait  (100); 
//            if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12)==0)  
//            {                
//                if(Speed_L>0)
//                {                    
//                    Speed_L=Speed_L-50;
//                    m_status = 1;
//                }
//            }
//        }
        os_dly_wait(30);
		} 
 }
 __task void StepAdd (void)          //到记步数反转
 {
	 while(1)
	 {
		 os_evt_wait_or(0x0100,0xFFFF);
		 m_status  = 1;		 
		 os_dly_wait(2);
	 }	 	 
 }
 __task void TimeAddust (void)          //校准时间任务，用完后注释
 {
	 os_itv_set (10);

	 while(1)
	 {
		 GPIOA->ODR ^=GPIO_Pin_3;
		 os_itv_wait ();
		 
	 }	 	 
 }
__task void init (void)                       
{
    //	os_tsk_create (TimeAddust, 10);
    // 	os_sem_init (&sem1, 0);
    t_StepMotor   = os_tsk_create (StepMotor, 10);	   //任务函数名、优先级
    t_Key     		= os_tsk_create (Key, 10);
    //		t_StepAdd    	= os_tsk_create (StepAdd, 10);
    t_LCD    			= os_tsk_create (LCD, 10);
    //		t_PWM    			= os_tsk_create (PWM, 10);
    //		t_Ultrasonic  = os_tsk_create (Ultrasonic, 10);
    os_tsk_delete_self ();         
}



int main (void) 
{
    Motor_GPIO_Config();
    
    BSP_LED_Init();
    BSP_LED_ON();

    TIM2_Configuration();																// TIM2定时器配置	 		
    TIM4_Configuration();

                                                                        //A11,12;C10,11,12	USART1_Config();
    NVIC_Configuration();	
    os_sys_init (init);                    
}
