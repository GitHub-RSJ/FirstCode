#ifndef TIME_TEST_H
#define TIME_TEST_H

#include "stm32f10x.h"
#include "stm32f10x_tim.h"
void TIM2_Configuration(void);
void TIM3_Mode_Config(void);
void TIM3_GPIO_Config(void) ;
void TIM4_Configuration(void );

void TIM4_Init(u16 arr,u16 psc);

#endif	/* TIME_TEST_H */
