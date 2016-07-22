#include "BSP_LCD.h"

void HAL_GPIO_Init(GPIO_TypeDef* GPIO_PORT,uint16_t GPIO_PIN)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    HAL_Open_PeriphClock(GPIO_PORT);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_PIN;               
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIO_PORT, &GPIO_InitStructure);
    GPIO_SetBits(GPIO_PORT,GPIO_PIN);    
}

static void HAL_Open_PeriphClock(GPIO_TypeDef*  GPIO_PORT)
{
    if(GPIO_PORT == GPIOA)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);     
    }
    else if(GPIO_PORT == GPIOB)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);     
    }
    else if(GPIO_PORT == GPIOC)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    }
    else if(GPIO_PORT == GPIOD)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    }
    else if(GPIO_PORT == GPIOE)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
    }
    else if(GPIO_PORT == GPIOF)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
    }
    else if(GPIO_PORT == GPIOG)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
    }
}

void LCDShiftWrite(u8 dat)   
{    
  u8 i;                                      
  u8 Series,Temp; 
	                                         
  Series = dat;   
  for(i=0; i<8; i++)   
  {   
    LCD_SCK_CLR;                              
    Temp=Series & 0x80;                    
    if(Temp)                              
    {   
      LCD_SDI_SET;                 
    }   
    else    
    {   
      LCD_SDI_CLR;                   
    } 
    LCD_SCK_SET;                            
    Series = Series << 1;               
  }   
}   


void send_cmd(u8 cmd, u8 dat)
{
  LCD_CS_CLR;
	LCD_DC_CLR;
  LCDShiftWrite(cmd|dat);
  LCD_CS_SET;
}

void send_dat(u8 dat)
{
    LCD_CS_CLR;
	LCD_DC_SET;
    LCDShiftWrite(dat);
    LCD_CS_SET;
}


void BSP_LCD_Init(void) 
{ 
    
    HAL_GPIO_Init(LCD_Port_Reset,LCD_Pin_Reset);
    HAL_GPIO_Init(LCD_Port_SDC,LCD_Pin_SDC);
    HAL_GPIO_Init(LCD_Port_SDI,LCD_Pin_SDI);
    HAL_GPIO_Init(LCD_Port_DC,LCD_Pin_DC);
    HAL_GPIO_Init(LCD_Port_CS,LCD_Pin_CS);
    HAL_GPIO_Init(LCD_Port_BKLight,LCD_Pin_BKLight);
    LCD_Reset_Reset;
    LCD_Reset_Set;  
    LCD_BKLight(ON);
    send_cmd(Function_Set,0x01);	
    send_cmd(Set_V0,0x30);	
    send_cmd(Set_Test_Mode,0x02);	
    send_cmd(Function_Set,0x00);	
    send_cmd(Display_Control,0x04);	
	BSP_LCD_Clean();

} 

void LCD_set_XY(unsigned char x,unsigned char y)
{
  send_cmd(Set_X_Address,x);
  send_cmd(Set_Y_Address,y);  
}

void BSP_LCD_Clean(void)
{
  int i;
  send_cmd(Set_X_Address,	0);
  send_cmd(Set_Y_Address,	0);
  for(i=0;i<960;i++)
    send_dat(0x00);
  send_cmd(Set_X_Address,	0);
  send_cmd(Set_Y_Address,	0);
}

void putch(unsigned char x, unsigned char y, unsigned int ch)
{
    unsigned char i;
    send_cmd(Set_X_Address,x);
    send_cmd(Set_Y_Address,y);
    for(i=0;i<5;i++)
    {
        send_dat(ASCII_font[(ch-0x20)*5+i]);
    }
}

void putstr(unsigned char x, unsigned char y, char *str)
{
  while(*str!=0)
  {
    putch(x,y,*str++);
    x=x+6;
  }
}


void SHOW_BMP(void)
{
  unsigned int i,j,n=0;
  for(i=0;i<8;i++)
    for(j=0;j<96;j++)
    {
      send_cmd(Set_Y_Address,i);
      send_cmd(Set_X_Address,j);   
      send_dat(BMP[n++]);
    }
}

/*-----------------------------------------------------------------------
LCD_write_chinese_string: 在LCD上显示汉字
输入参数：X、Y    ：显示汉字的起始X、Y坐标；
          ch_with ：汉字点阵的宽度
          num     ：显示汉字的个数；  
          line    ：汉字点阵数组中的起始行数
          row     ：汉字显示的行间距
-----------------------------------------------------------------------*/ 
void LCD_write_chinese_string(unsigned char X, unsigned char Y, 
                   unsigned char ch_with,unsigned char num,
                   unsigned char line,unsigned char row)
{
  unsigned char i,n; 
  LCD_set_XY(X,Y);                             //设置初始位置  
  for (i=0;i<num;)
  {
     for (n=0; n<ch_with*2; n++)              //写一个汉字
    { 
      if (n==ch_with)                      //写汉字的下半部分
      {
        if (i==0) LCD_set_XY(X,Y-1);
        else
        LCD_set_XY((X+(ch_with+row)*i),Y-1);
      }
      send_dat(Chinese_font[line+i][n]);
    }
    i++;
    LCD_set_XY((X+(ch_with+row)*i),Y);
  }
}
