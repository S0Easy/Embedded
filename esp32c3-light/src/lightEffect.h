//流水灯定义
#ifndef lightEffect_H
#define lightEffect_H


#define COLOR_ORDER GRB
#define CHIPSET     WS2812
#define FRAMES_PER_SECOND 60
#define LED_TYPE    WS2812
#define DELAY_TIME 10



void runningLight();
void setupLight();


//Adafruit_NeoPixel 实现流水灯，但是没有反应，问题未解决
void setupLight2();


//fastled库实现跟着声音跳动的灯效果
void jumpLight();

//fastled库使用fill_palette实现海浪效果
void waveLight();
void breathLight();

//fastled库实现灯带音频闪烁
void audioLight();


#endif
