#ifndef __BSP_LED
#define __BSP_LED

#include "stm32f10x_conf.h"
#include "BSP_PinCOnfig.h"

#define BSP_LED_ON()   GPIO_ResetBits(LED_Port,LED_Pin)
#define BSP_LED_OFF()  GPIO_SetBits(LED_Port,LED_Pin)

#define Motor_A_DIS  GPIO_ResetBits(GPIOA,GPIO_Pin_6)
#define Motor_B_DIS  GPIO_ResetBits(GPIOB,GPIO_Pin_3)
#define Motor_A_EN   GPIO_SetBits(GPIOA,GPIO_Pin_6)
#define Motor_B_EN  GPIO_SetBits(GPIOB,GPIO_Pin_3)

void BSP_LED_Init(void);
void Motor_GPIO_Config(void);
void Key_GPIO_Config(void);
//void BSP_LED_ON();
//void BSP_LED_OFF();

#endif 
