// This supresses the pragma version warning FASTLED produces
#define FASTLED_INTERNAL
#include <FastLED.h>
#include "ChristmasLights.h"
#include "pleaseWait.h"

boolean debug = true;

// WS2812B LED Data Pin
const int ledPin = 7;

unsigned char brightness = 60;

#define NUM_LEDS 22
CRGB leds[NUM_LEDS];

// Christmas Colors
CRGB colors[] = { 0xFF0000, 0x00FF00, 0x0000FF, 0xFFFF00 };
unsigned char numColors = sizeof(colors) / sizeof(CRGB);
ChristmasLights  myChristmasLights(&leds[0], NUM_LEDS,
                                   &colors[0], numColors);
boolean christmasOn = false;

pleaseWait myPleaseWait(&leds[0], NUM_LEDS,
                        5, 0.80, 3.0, 1.0, 0x00FFFF);


void setup() {
  Serial.begin(57600);

  if (debug) {
    Serial.println("DEBUG ON");
  }

  FastLED.addLeds<NEOPIXEL, ledPin>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.setBrightness(brightness);
  FastLED.show();

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  myPleaseWait.start();
}

void loop() {
  // put your main code here, to run repeatedly:
//  myChristmasLights.loop();
  myPleaseWait.clear();
  myPleaseWait.loop();
  FastLED.show();
}
