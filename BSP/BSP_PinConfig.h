// Pinmap

#ifndef __BSP_PINCONFIG
#define __BSP_PINCONFIG

#define LED_Port GPIOB
#define LED_Pin  GPIO_Pin_0



#define Button_1_Port GPIOB
#define Button_1_pin  GPIO_Pin_2

#define Button_2_Port GPIOA
#define Button_2_pin  GPIO_Pin_10

#define Button_3_Port GPIOA
#define Button_3_pin  GPIO_Pin_12



#define Motor_1_Clk_Port		GPIOA
#define Motor_1_Clk_Pin		  GPIO_Pin_0

#define Motor_1_Dir_Port		GPIOA
#define Motor_1_Dir_Pin		  GPIO_Pin_2

#define Motor_1_EN_Port		  GPIOA
#define Motor_1_EN_Pin		  GPIO_Pin_4

#define Motor_2_Clk_Port		GPIOB
#define Motor_2_Clk_Pin		  GPIO_Pin_7

#define Motor_2_Dir_Port		GPIOB
#define Motor_2_Dir_Pin		  GPIO_Pin_5

#define Motor_2_EN_Port		  GPIOB
#define Motor_2_EN_Pin		  GPIO_Pin_3

#endif
