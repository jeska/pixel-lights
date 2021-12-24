#include <FastLED.h>

#define NUM_LEDS 100
#define NUM_ROWS 5
#define ROW_LEN  20

#define IN_PIN   0
#define DATA_PIN 6
#define LED_TYPE WS2811

CRGB leds[NUM_LEDS];
// int rows[20][5];

CRGBPalette16 currentPalette;
TBlendType    currentBlending;
const TProgmemPalette16 EffinChristmas_p PROGMEM =
{
    CRGB::DarkRed,
    CRGB::DarkRed,
    CRGB::Red,
    CRGB::Red,
    
    CRGB::OrangeRed,
    CRGB::OrangeRed,
    CRGB::Gold,
    CRGB::Gold,
    
    CRGB::GreenYellow,
    CRGB::GreenYellow,
    CRGB::Green,
    CRGB::Green,
    CRGB::ForestGreen,
    CRGB::ForestGreen,
    CRGB::Brown,
    CRGB::Brown
};


int brightnessLPF = 0;

void setup() {
  Serial.begin(9600);
  delay(2000);
  FastLED.addLeds<LED_TYPE, DATA_PIN, RGB>(leds, NUM_LEDS).setCorrection(TypicalPixelString);
//  currentPalette = EffinChristmas_p;
//  currentBlending = LINEARBLEND;
}

void loop() {
// Fade through our Effin' Christmas palette
//  static uint8_t startIndex = 0;
//  startIndex = startIndex + 1;
//  PaletteFadeByRows(startIndex);

// Use an analog input to set the brightness; WIP 
//  BrightnessFromAnalog();

// Red/Green Adventures
  RedGreenAlternate();
}


void PaletteFadeByRows(uint8_t colorIndex) {
  int brightness = 255;
  for(int l = 0; l < ROW_LEN; l++) {
    for(int r = 0; r < NUM_ROWS; r++) {
      leds[LedIndexAdjustment(r * ROW_LEN + l)] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
      colorIndex += 3;
    }
  }
  FastLED.show();
  delay(20);
}

// WIP: working on matching to microphone
void BrightnessFromAnalog() {
  int analogIn = analogRead(0);
  int brightness = 0;
  int threshold = 512;
  if(analogIn > threshold) {
    float adj = (analogIn - threshold) * 256.0 / 2;
    brightness = round(adj);

    if (brightness > brightnessLPF)
    {
      brightnessLPF = brightness;
    }
    else
    {
      brightness = brightnessLPF;
      brightnessLPF -= 1;

      if (brightnessLPF < 10)
        brightnessLPF = 10;
    }
  }
  
  int colorIndex = 0;
  for(int l = 0; l < ROW_LEN; l++) {
    for(int r = 0; r < NUM_ROWS; r++) {
      leds[LedIndexAdjustment(r * ROW_LEN + l)] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
      colorIndex += 5;
    }
  }
  FastLED.show();
}


void RedGreenAlternate() {
  for(int h = HUE_RED; h <= HUE_GREEN; h++) {
    for(int l = 0; l < NUM_LEDS; l++) {
      if(l % 2 == 0) {
        leds[l] = CHSV(h,255,255);
      } else {
        leds[l] = CHSV(HUE_GREEN - h,255,255);
      }
    }
    FastLED.show();
    delay(10);
  }
  delay(1000);
  
  for(int h = HUE_RED; h <= HUE_GREEN; h++) {
    for(int l = 0; l < NUM_LEDS; l++) {
      if(l % 2 == 0) {
        leds[l] = CHSV(HUE_GREEN - h,255,255);
      } else {
        leds[l] = CHSV(h,255,255);
      }
    }
    FastLED.show();
    delay(10);
  }
  delay(1000);
}

// Our lights are snaked vertically; convert the 0-99 index to the right row/col pair
int LedIndexAdjustment(int pos) {
  if(pos >= 20 && pos < 40) {
    return 40 + 19 - pos;
  } else if(pos >= 60 && pos < 80) {
    return 80 + 59 - pos;
  } else {
    return pos;
  }
}
