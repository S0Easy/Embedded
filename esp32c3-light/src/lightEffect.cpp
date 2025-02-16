//调用fastled库,实现流水灯效果
#include <FastLED.h>
#include <lightEffect.h>
#include <common.h>


// 实现流水灯效果
bool gReverseDirection = false;
CRGB breathLeds[BREATHERLIGHTCOUNT];
CRGB runingLeds[RUNNINGLIGHTCOUNT];
CRGBPalette16 gPal;

//海浪灯光效果
CRGBPalette16 myColorPalette = CRGBPalette16(  //用户自定义RGB色板
                                CRGB::Green,  CRGB::Green,  CRGB::Black,  CRGB::Black,  
                                CRGB::Purple, CRGB::Purple, CRGB::Black,  CRGB::Black,
                                CRGB::Green,  CRGB::Green,  CRGB::Black,  CRGB::Black,
                                CRGB::Purple, CRGB::Purple, CRGB::Black,  CRGB::Black );
                          
CHSVPalette16 myHSVColorPalette = CHSVPalette16 ( //用户自定义HSV色板
                   CHSV(0, 255, 200),  CHSV(15, 255, 200),  CHSV(31, 255, 200), CHSV(47, 255, 200),
                   CHSV(0, 255, 0),    CHSV(15, 255, 0),    CHSV(31, 255, 0),   CHSV(47, 255, 0),
                   CHSV(0, 255, 200),  CHSV(15, 255, 200),  CHSV(31, 255, 200), CHSV(47, 255, 200),
                   CHSV(0, 0, 200),    CHSV(15, 0, 200),    CHSV(31, 0, 200),   CHSV(47, 0, 200));   


CHSVPalette16 singleHSVColorPalette = CHSVPalette16(
  CHSV(14, 255, 200), CHSV(14, 255, 200), CHSV(14, 255, 200), CHSV(14, 255, 200),
  CHSV(14, 255, 0), CHSV(14, 255, 0), CHSV(14, 255, 0), CHSV(14, 255, 0),
  CHSV(14, 255, 200), CHSV(14, 255, 200), CHSV(14, 255, 200), CHSV(14, 255, 200),
  CHSV(14, 255, 0), CHSV(14, 255, 0), CHSV(14, 255, 0), CHSV(14, 255, 0)
);


                  
                               
const TProgmemPalette16 myProgmemPalette PROGMEM = { //用户自定义PROGMEM色板
                              CRGB::Red,  CRGB::Gray,  CRGB::Blue,   CRGB::Black,
                              CRGB::Red,  CRGB::Gray,  CRGB::Blue,   CRGB::Black,
                              CRGB::Red,  CRGB::Red,   CRGB::Gray,   CRGB::Gray,
                              CRGB::Blue, CRGB::Blue,  CRGB::Black,  CRGB::Black };    

//
uint8_t colorIndex;
uint8_t startIndex;



void setupLight() {
  FastLED.addLeds<LED_TYPE , 18, COLOR_ORDER>(runingLeds, RUNNINGLIGHTCOUNT); 
  FastLED.addLeds<LED_TYPE, 19, COLOR_ORDER>(breathLeds, BREATHERLIGHTCOUNT );
  FastLED.setBrightness(BRIGHTNESS);
  
}

//fastled库实现流水灯效果
void runningLight() {
  Serial.println("runningLight");
  for (int i = 0; i < RUNNINGLIGHTCOUNT; i++) {
    runingLeds[(i - 1 + RUNNINGLIGHTCOUNT) % RUNNINGLIGHTCOUNT] = CRGB::Blue;
    runingLeds[i] = CRGB::Blue;
    runingLeds[(i + 1) % RUNNINGLIGHTCOUNT] = CRGB::Blue;
    FastLED.show();
    delay(50); // Add a small delay to make the effect visible
    runingLeds[(i - 1 + RUNNINGLIGHTCOUNT) % RUNNINGLIGHTCOUNT] = CRGB::Black;
    runingLeds[i] = CRGB::Black;
    runingLeds[(i + 1) % RUNNINGLIGHTCOUNT] = CRGB::Black;
  }
}

//fastled库实现呼吸灯效果
// void breathLight() {
//   uint8_t brightness = beatsin8(60, 50, 200); // 计算亮度
//   Serial.println("breathLight");
//   // CHSV 是 FastLED 中的一种颜色表示方式，H 表示色相，S 表示饱和度，V 表示亮度
//   // 随机色相范围是 0-255，随机饱和度范围是 0-255，亮度使用计算得到的 brightness
//   uint8_t h = random(0,256);
//   uint8_t s = random(0,256);
//   // 设置所有 LED 的亮度为计算得到的 brightness
//   for (int i = 0; i < BREATHERLIGHTCOUNT; i++) {
//     breathLeds[i] = CHSV(h, s, brightness); // 使用 CHSV 设置颜色和亮度
//     FastLED.show();
//   };
//   delay(50); // 添加小延迟以使效果可见
// }

void breathLight() {
  uint8_t brightness = beatsin8(60, 50, 200); // 计算亮度
  Serial.println("breathLight");

  // 为每个灯珠生成不同的色相和饱和度
  for (int i = 0; i < BREATHERLIGHTCOUNT; i++) {
    // uint8_t h = map(i, 0, BREATHERLIGHTCOUNT, 0, 255); // 生成不同的色相
    uint8_t h = random(0,256);
    uint8_t s = random(128, 255); // 生成随机的饱和度
    breathLeds[i] = CHSV(h, s, brightness); // 使用 CHSV 设置颜色和亮度
    uint8_t brightness = beatsin8(60, 50, 200);
    delay(5);
  }
  FastLED.show(); // 显示所有 LED
}
//fastled库实现跟着声音跳动的灯效果
void jumpLight(int brightness) {
  runingLeds[RUNNINGLIGHTCOUNT] = CRGB::Blue;
  FastLED.setBrightness(brightness);
  FastLED.show();
  delay(50); // Add a small delay to make the effect visible
  runingLeds[RUNNINGLIGHTCOUNT] = CRGB::Black;
}



//海浪灯光效果
void waveLight() {
  startIndex++;
  Serial.println("runningLight");       
  fill_palette (runingLeds,    RUNNINGLIGHTCOUNT,   startIndex,          10,            OceanColors_p, 125,   LINEARBLEND ); 
  FastLED.show();
}
