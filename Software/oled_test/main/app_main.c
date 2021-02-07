/* SPI Master Half Duplex EEPROM example.

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"

#include "sdkconfig.h"
#include "esp_log.h"
#include "oled.h"

void app_main(void)
{
    while (1) {
        printf("Hello World\n");
        vTaskDelay(5000 / 10);
        OLED_Init();			//初始化OLED  
        OLED_Clear();
        OLED_ShowCHinese(0,0,0);//中
        OLED_ShowCHinese(18,0,1);//景
        OLED_ShowCHinese(36,0,2);//园
        OLED_ShowCHinese(54,0,3);//电
        OLED_ShowCHinese(72,0,4);//子
        OLED_ShowCHinese(90,0,5);//科
        OLED_ShowCHinese(108,0,6);//技
        OLED_ShowString(0,3,(uint8_t *)"1.3' OLED TEST");
    }
}
