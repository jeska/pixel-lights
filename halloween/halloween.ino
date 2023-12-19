#include <FastLED.h>

#define NUM_LEDS    100

#define NUM_OFF     5
#define NUM_ORANGE  85
#define NUM_GREEN   10

#define IN_PIN      0
#define DATA_PIN    6
#define LED_TYPE    WS2811

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600);
  delay(2000);
  FastLED.addLeds<LED_TYPE, DATA_PIN, RGB>(leds, NUM_LEDS).setCorrection(TypicalPixelString);
}

void loop() {
  // Let's make a pumpkin!

  // Keep some LEDs off
  for(int off = 0; off < NUM_OFF; off++) {
      leds[off] = CRGB(0,0,0);
  }

  // Orange pumpkin
  int org_start = NUM_OFF;
  for(int org = 0; org < NUM_ORANGE; org++) {
      leds[org_start + org] = CRGB(255,165,0);
  }

  // Green stem
  int grn_start = NUM_OFF + NUM_ORANGE;
  for(int grn = 0; grn < NUM_GREEN; grn++) {
      leds[grn_start + grn] = CRGB(0,255,0);
  }

  FastLED.show();
  delay(10);
}
