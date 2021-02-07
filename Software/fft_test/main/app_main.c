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
#include "esp_system.h"


#include "sdkconfig.h"
#include "esp_log.h"
#include "esp_dsp.h"

#include <math.h>

#define N_SAMPLES 1024
#define PI (3.14159f)

static const char *TAG = "main";
int N = N_SAMPLES;
float cpx_ary[N_SAMPLES * 2];
float wind[N_SAMPLES];
float mag_out[N_SAMPLES];//输出幅度值
float fs = 10000.0;//采样率
float f1 = 440;
float f2 = 2200;

int max_index(float* buff, int len)
{
    float m = 0;
    int index = 0;
    for (size_t i = 0; i < len; i++)
    {
        if( buff[i] > m)
        {
            m = buff[i];
            index = i;
        }
    }
    return index;
}

void dsp_init(void)
{    
    esp_err_t ret;
    ESP_LOGI(TAG, "Start Example.");
    ret = dsps_fft2r_init_fc32(NULL, CONFIG_DSP_MAX_FFT_SIZE);
    if (ret  != ESP_OK)
    {
        ESP_LOGE(TAG, "Not possible to initialize FFT. Error = %i", ret);
        return;
    }
}

void data_gen(void)
{
    dsps_wind_hann_f32(wind, N);

    for (size_t i = 0; i < 1024; i++)
    {
        // cpx_ary[2 * i] = (sin(2 * PI * f1 / fs * i) + sin(2 * PI * f2 / fs * i)) * wind[i];
        cpx_ary[2 * i] = sin(2 * PI * f1 / fs * i) * wind[i];
        cpx_ary[2 * i + 1] = 0;
    }
}

void data_process(void)
{
    dsps_fft2r_fc32(cpx_ary, N);
    dsps_bit_rev_fc32(cpx_ary, N);
    dsps_cplx2reC_fc32(cpx_ary, N);

    for (size_t i = 0; i < N; i++)
    {
        // mag_out[i] = 10 * log10f(cpx_ary[2 * i] * cpx_ary[2 * i] + 
        // cpx_ary[2 * i + 1] * cpx_ary[2 * i + 1] ) / N;
          mag_out[i] = 10*log10f((cpx_ary[2 * i] * cpx_ary[2 * i] + cpx_ary[2 * i + 1] * cpx_ary[2 * i + 1])/N);
    }
    ESP_LOGW(TAG, "Signal mag_out");
    dsps_view(mag_out, N, 64, 10,  -60, 40, '|');
    int idx = max_index(cpx_ary, N / 2);
    printf("MAX index = %d\n", idx);
    printf("so freq = %0.2f\n", fs * 2 * idx / (float) N);
}


void app_main(void)
{
    dsp_init();
    while (1) {
        printf("Hello World\n");
        data_gen();
        data_process();
        vTaskDelay(5000 / 10);
    }
}
