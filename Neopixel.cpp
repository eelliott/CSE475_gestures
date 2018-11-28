#include "Neopixel.h"
#include "Debug.h"

// Initialize fixed list of light gestures.
constexpr void (*Neopixel::LIGHTS[])(uint32_t);

uint8_t Neopixel::_currentIdx = 0;
uint32_t Neopixel::_lastLoop = 0;
Adafruit_NeoPixel_ZeroDMA Neopixel::_strip = Adafruit_NeoPixel_ZeroDMA(NEOPIXEL_COUNT, NEOPIXEL_PIN, NEO_GRBW);

void Neopixel::setup() {
  _strip.begin();
  _strip.setBrightness(5);
  _strip.show();
}

void Neopixel::loop() {
    uint32_t thisLoop = millis();
    uint32_t dt;
    if (_lastLoop) {
        dt = thisLoop - _lastLoop;
    } else {
        dt = 0;
    }
    _lastLoop = thisLoop;

    if (LIGHTS[_currentIdx] != nullptr) {
        LIGHTS[_currentIdx](dt);
    }
}

void Neopixel::setLight(uint8_t lightIdx) {
  // lightIdx soundIdx. Anything outside of the bounds of the array is 0.
  if (lightIdx >= sizeof(LIGHTS) / sizeof(void*)) {
    lightIdx = 0;
  }

  if (_currentIdx != lightIdx) {
    _strip.clear();
    _strip.show();

    _currentIdx = lightIdx;
  }
}

uint8_t Neopixel::getLight() {
  return _currentIdx;
}

void Neopixel::rainbow(uint32_t dt) {
  static uint8_t offset = 0;
  static uint32_t rainbowColors[NEOPIXEL_COUNT] = {16711680, 13578240, 10444800, 7311360, 4177920, 1044480, 56865, 44625,
                                                   32385, 20145, 7905, 1179885, 4325565, 7471245, 10616925, 13762605};

  if (dt > 50) {
    for (uint8_t pix = 0; pix < NEOPIXEL_COUNT; pix++) {
      _strip.setPixelColor((pix + offset) % NEOPIXEL_COUNT, rainbowColors[pix]);
    }
    _strip.show();
    offset++;
  }
}

void Neopixel::orangeQuad(uint32_t dt){
  uint16_t i;
  uint8_t R, G, B;

  if (dt > 50) {
    uint8_t rand = random(4);
    B = 0;
    for(i = 0; i < 16; i++) {
      switch (rand) {
        case 0:
          if (i >= 0 && i < 4) {
            R = 255;
            G = 100;
          } else {
            R = 0;
            G = 0;
          }
          break;
        case 1:
          if (i >= 4 && i < 8) {
            R = 255;
            G = 100;
          } else {
            R = 0;
            G = 0;
          }
          break;
        case 2:
          if (i >= 8 && i < 12) {
            R = 255;
            G = 100;
          } else {
            R = 0;
            G = 0;
          }
          break;
        case 3:
          if (i >= 12 && i < 16) {
            R = 255;
            G = 100;
          } else {
            R = 0;
            G = 0;
          }
          break;   
        default:
          break;
      }
      _strip.setPixelColor(i, _strip.Color(R, G, B));
    }
    _strip.show();
  }
}

byte rainDropState[16];
byte rainShineState[16];
byte rainDropVolume[16];
byte rainShineVolume[16];

void Neopixel::rainCycle(uint32_t dt) {
  uint16_t i;

  if (dt > 50) {
    for(i = 0; i < 16; i++){
      Rain((rainDropState + i), (rainShineState + i), (rainDropVolume + i), (rainShineVolume + i)); 
    }
    
    for(i = 0; i < 16; i++){
      _strip.setPixelColor(i, _strip.Color(0, 0, *(rainDropVolume + i), *(rainShineVolume + i)));
    }
    _strip.show();
  }
}

void Neopixel::Rain(byte* rds, byte* rss, byte* rdv, byte* rsv) {
  uint16_t i;
  
  if(*rds == 0){
    if(random(16) <= 1){
      *rds = 1;
    }
  }

  if (*rds == 1){
    i = random(250);
    if ((i + *rdv) >= 250){
      *rdv = 250; 
      *rds = 2;
      *rss = 1;
    } else {
      *rdv = *rdv + i;
    }
  } else if(*rds == 2) {
    i = random(100);
    if ((*rdv - i) <= 0) {
      *rdv = 0; 
      *rds = 0;
    } else {
      *rdv = *rdv - i;
    }

    if(*rss == 1){
      i = random(500);
      if((i + *rsv) >= 250){
        *rsv = 250; 
        *rss = 2;
      }else{
        *rsv = *rsv + i;
      }
    }else if(*rss == 2){
      i = random(250);
      if((*rsv - i) <= 0){
        *rsv = 0; 
        *rss = 0;
      }else{
        *rsv = *rsv - i;
      }
    }
  }
  
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Neopixel::Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return _strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return _strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return _strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
