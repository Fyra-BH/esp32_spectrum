//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//中景园电子
//店铺地址：http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  文 件 名   : main.c
//  版 本 号   : v2.0
//  作    者   : HuangKai
//  生成日期   : 2014-0101
//  最近修改   : 
//  功能描述   : OLED 4接口演示例程(51系列)
//              说明: 
//              ----------------------------------------------------------------
//              GND    电源地
//              VCC  接5V或3.3v电源
//              D0   接PA5（SCL）
//              D1   接PA7（SDA）
//              RES  接PB0
//              DC   接PB1
//              CS   接PA4               
//              ----------------------------------------------------------------
// 修改历史   :
// 日    期   : 
// 作    者   : HuangKai
// 修改内容   : 创建文件
//版权所有，盗版必究。
//Copyright(C) 中景园电子2014/3/16
//All rights reserved
//******************************************************************************/
#ifndef __OLED_H
#define __OLED_H	
//from esp-idf		  	 
#include "driver/gpio.h"

#include "stdlib.h"	   
#include "stdint.h"	  

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

//OLED模式设置
//0:4线串行模式
//1:并行8080模式
#define OLED_MODE 0
#define SIZE 16
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    


#define GPIO_SCL_PIN  12
#define GPIO_SDI_PIN  14
#define GPIO_RST_PIN  27
#define GPIO_DC_PIN  26
#define GPIO_CS_PIN  25

#define GPIO_OUTPUT_PIN_SEL  ((1ULL<<GPIO_SCL_PIN) | (1ULL<<GPIO_SDI_PIN) | \
 (1ULL<<GPIO_RST_PIN) | (1ULL<<GPIO_DC_PIN) | (1ULL<<GPIO_CS_PIN))

#define delay_ms(X) vTaskDelay(X/10)

//-----------------测试LED端口定义---------------- 
// #define LED_ON GPIO_ResetBits(GPIOB,GPIO_Pin_8)//DC
// #define LED_OFF GPIO_SetBits(GPIOB,GPIO_Pin_8)

//-----------------OLED端口定义----------------  					   


// #define OLED_SCLK_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_5)//CLK
// #define OLED_SCLK_Set() GPIO_SetBits(GPIOA,GPIO_Pin_5)

// #define OLED_SDIN_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_7)//DIN
// #define OLED_SDIN_Set() GPIO_SetBits(GPIOA,GPIO_Pin_7)

// #define OLED_RST_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_0)//RES
// #define OLED_RST_Set() GPIO_SetBits(GPIOB,GPIO_Pin_0)

// #define OLED_DC_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_1)//DC
// #define OLED_DC_Set() GPIO_SetBits(GPIOB,GPIO_Pin_1)
 		     
// #define OLED_CS_Clr()  GPIO_ResetBits(GPIOA,GPIO_Pin_4)//CS
// #define OLED_CS_Set()  GPIO_SetBits(GPIOA,GPIO_Pin_4)


#define OLED_SCLK_Clr() gpio_set_level(GPIO_SCL_PIN, 0)
#define OLED_SCLK_Set() gpio_set_level(GPIO_SCL_PIN, 1)

#define OLED_SDIN_Clr() gpio_set_level(GPIO_SDI_PIN, 0)//DIN
#define OLED_SDIN_Set() gpio_set_level(GPIO_SDI_PIN, 1)

#define OLED_RST_Clr() gpio_set_level(GPIO_RST_PIN, 0)//DIN//RES
#define OLED_RST_Set() gpio_set_level(GPIO_RST_PIN, 1)

#define OLED_DC_Clr() gpio_set_level(GPIO_DC_PIN, 0)//DC
#define OLED_DC_Set() gpio_set_level(GPIO_DC_PIN, 1)
 		     
#define OLED_CS_Clr() gpio_set_level(GPIO_CS_PIN, 0)//CS
#define OLED_CS_Set() gpio_set_level(GPIO_CS_PIN, 1)


#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据


//OLED控制用函数
void OLED_WR_Byte(uint8_t dat,uint8_t cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t);
void OLED_Fill(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t dot);
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr);
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size);
void OLED_ShowString(uint8_t x,uint8_t y, uint8_t *p);	 
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
#endif  
	 



