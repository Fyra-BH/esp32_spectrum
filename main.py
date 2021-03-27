from ezfft import *
from math import *
import array, time, gc
from machine import Pin, SoftSPI
from ssd1306 import SSD1306_SPI
import i2s_adc
import _thread
import machine

machine.freq(240000000)
i2s_adc.init(20000)
LED = Pin(18, Pin.OUT)
LED.on()

KEY1 = Pin(5, Pin.IN)
KEY2 = Pin(17, Pin.IN)
KEY3 = Pin(16, Pin.IN)
KEY4 = Pin(4, Pin.IN)

spi = SoftSPI(baudrate=100000, polarity=1, phase=0, sck=Pin(12), mosi=Pin(14), miso=Pin(21))
oled = SSD1306_SPI(128, 64, spi, Pin(26, Pin.OUT), Pin(27, Pin.OUT), Pin(10, Pin.OUT))
oled.show()   #OLED执行显示
top, downstep = [0.]*64, 2 # 用于存放最上面的点
x1 = array.array('f',[0]*1024)
mark = 5

def run():
    while True:
        start = time.ticks_ms()
        oled.fill(0)
        i2s_adc.read_to_array(x1)
        fft_real(x1)
        x = ezabs(x1)[0:128]
        # 确定缩放系数 限定在mark以内
        ruler = 64 / (max(x[2:64]) + 0.001)
        ruler = mark if ruler > mark else ruler
        for i in range(64):
            # 舍弃前两个点（直流分量）
            top[i] = top[i] - downstep / ruler if top[i] > x[i + 2] else x[i + 2]
            if top[i] < 0: top[i] = 0
            oled.fill_rect((i+2)*2, 63 - int(x[i+2] * ruler), 2, int(x[i+2] * ruler) + 1 , 1)
            oled.fill_rect((i+2)*2, 63 - int(top[i] * ruler), 2, 2, 1)
        gc.collect()
        end = time.ticks_ms()
        fps = 1000/(end - start);
#         oled.text("fps=" + str(round(fps,1)), 60, 0)
        oled.show()

_thread.start_new_thread(run,[])        

def key1_irq(arg):
    global mark
    if mark < 10: mark += 0.5
    
def key2_irq(arg):
    global mark
    if mark > 0.5: mark -= 0.5

def key3_irq(arg):
    global downstep
    if downstep < 10: downstep += 0.5
    
def key4_irq(arg):
    global downstep
    if downstep > 1: downstep -= 0.5

KEY1.irq(trigger=Pin.IRQ_FALLING, handler=key1_irq)
KEY2.irq(trigger=Pin.IRQ_FALLING, handler=key2_irq)
KEY3.irq(trigger=Pin.IRQ_FALLING, handler=key3_irq)
KEY4.irq(trigger=Pin.IRQ_FALLING, handler=key4_irq)


