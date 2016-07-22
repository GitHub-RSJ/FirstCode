#ifndef _DELAY_H
#define _DELAY_H

#include"stm32f10x.h"

//工程用于浙江大学宁波理工电子竞赛
//创建日期:2015.06.06建立 作者那片清茶
//公司：宁波芯瑞格电子科技有限公司
//版本：V1.1
//版权所有，盗版必究。
//Copyright(C) 宁波市芯瑞格电子科技有限公司 2015-2025
//All rights reserved

void  Delay(__IO u32 count);
/*--------------------------------- 
描 述：参数1即为1ms，1000即为1s；只有几
us的误差；
-----------------------------------*/
extern void Delayms(__IO uint32_t nTime);
/*---------------------------------
描 述：参数1即为1us，1000即为1ms；只有几
us的误差；
-----------------------------------*/
extern void Delayus(__IO uint32_t nTime);
/*---------------------------------
函数名：延时调整形式的delaynus函数, 
描 述：参数1即为1us，1000即为1ms；
-----------------------------------*/
extern void delay_nus(unsigned long n);
/*---------------------------------
函数名：延时调整形式的delaynms函数, 
描 述：参数1即为1ms，1000即为1s；
-----------------------------------*/
extern void delay_nms(unsigned long n);

#endif
