#ifndef __BSP_LCD_H
#define __BSP_LCD_H		
#include "stdint.h" 

#include "stm32f10x_conf.h"
#include "ASCII_font.h" 
#include "Chinese_font.h"
#include "BMP_data.h"

#define HAL_GPIO_SetHigh(GPIO_PORT,GPIO_PIN)   GPIO_SetBits(GPIO_PORT,GPIO_PIN)
#define HAL_GPIO_SetLow(GPIO_PORT,GPIO_PIN)    GPIO_ResetBits(GPIO_PORT,GPIO_PIN)



#ifndef ON
#define ON      0
#endif
#ifndef OFF
#define OFF     1
#endif
 
/*
*******************************************************************************
*                         LCD GPIO Port define
*******************************************************************************
*/

#define LCD_Port_Reset      GPIOB
#define LCD_Pin_Reset       GPIO_Pin_15              //Reset LCD

#define LCD_Port_SDC        GPIOB
#define LCD_Pin_SDC         GPIO_Pin_14             //Serial Data Clk

#define LCD_Port_SDI        GPIOB
#define LCD_Pin_SDI         GPIO_Pin_12              //Serial Data In

#define LCD_Port_DC         GPIOB
#define LCD_Pin_DC          GPIO_Pin_13              //Data or Command

#define LCD_Port_CS         GPIOB
#define LCD_Pin_CS          GPIO_Pin_10             //Chip select

#define LCD_Port_BKLight    GPIOA
#define LCD_Pin_BKLight     GPIO_Pin_8              //Backlight

#define LCD_BKLight(temp)   if (temp) HAL_GPIO_SetHigh(LCD_Port_BKLight,LCD_Pin_BKLight); \
                            else    HAL_GPIO_SetLow(LCD_Port_BKLight,LCD_Pin_BKLight)     
    
                            

#define LCD_Reset_Reset	GPIO_ResetBits(LCD_Port_Reset,LCD_Pin_Reset);
#define LCD_Reset_Set    GPIO_SetBits(LCD_Port_Reset,LCD_Pin_Reset);

#define	LCD_CS_SET  GPIO_SetBits(LCD_Port_CS,LCD_Pin_CS)    //片选端口  	 PC9
#define	LCD_DC_SET	GPIO_SetBits(LCD_Port_DC,LCD_Pin_DC)    //数据/命令    PC8	   
#define	LCD_SDI_SET	GPIO_SetBits(LCD_Port_SDI,LCD_Pin_SDI)    //数据			   PC7
#define	LCD_SCK_SET	GPIO_SetBits(LCD_Port_SDC,LCD_Pin_SDC)    //时钟    		 PC6
								    
#define	LCD_CS_CLR  GPIO_ResetBits(LCD_Port_CS,LCD_Pin_CS)     //片选端口  PC9
#define	LCD_DC_CLR	GPIO_ResetBits(LCD_Port_DC,LCD_Pin_DC)     //数据/命令 PC8	   
#define	LCD_SDI_CLR	GPIO_ResetBits(LCD_Port_SDI,LCD_Pin_SDI)     //数据			 PC7
#define	LCD_SCK_CLR	GPIO_ResetBits(LCD_Port_SDC,LCD_Pin_SDC)     //时钟			 PC6	  					    					  
	
/*
*******************************************************************************
*                         LCD Command define
*******************************************************************************
*/
#define NOP		            0x00
#define Function_Set		0x20
#define Display_Control	    0x08
#define Set_Y_Address		0x40
#define Set_X_Address		0x80
#define Set_V0			    0x80
#define Set_Test_Mode		0x30


/*
*******************************************************************************
*                         LCD Function define
*******************************************************************************
*/
void BSP_LCD_Init(void);
void LCD_set_XY(unsigned char x,unsigned char y);
void BSP_LCD_Clean(void);
void putch(unsigned char x, unsigned char y, unsigned int ch);
void putstr(unsigned char x, unsigned char y, char *str);
void SHOW_BMP(void);
void LCD_write_chinese_string(unsigned char X, unsigned char Y, 
                   unsigned char ch_with,unsigned char num,
                   unsigned char line,unsigned char row);
									 
void HAL_GPIO_Init(GPIO_TypeDef* GPIO_PORT,uint16_t GPIO_PIN);
static void HAL_Open_PeriphClock(GPIO_TypeDef*  GPIO_PORT);
                   
#endif  
