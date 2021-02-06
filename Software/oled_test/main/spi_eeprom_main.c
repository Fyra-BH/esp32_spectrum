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
#include "fun_add.h"


void app_main(void)
{

    while (1) {
        printf("Hello World\n");
        printf("3 + 4 = %d\n",test_add(3, 4));
        // Add your main loop handling code here.
        vTaskDelay(1000 / 10);
    }
}
