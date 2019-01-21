// This supresses the pragma version warning FASTLED produces
#define FASTLED_INTERNAL
#include <FastLED.h>
#include "ChristmasLights.h"
#include "larsonScanner.h"
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
                        5, 2.5, 0x00FFFF);

larsonScanner myLarsonScanner(&leds[0], NUM_LEDS, 0xFF0000, 10000, 5);
larsonScanner myLarsonScanner2(&leds[0], NUM_LEDS, 0x00FF00, 11100, 5);
larsonScanner myLarsonScanner3(&leds[0], NUM_LEDS, 0x0000FF, 12200, 5);
larsonScanner myLarsonScanner4(&leds[0], NUM_LEDS, 0xFF00FF, 13300, 5);
larsonScanner myLarsonScanner5(&leds[0], NUM_LEDS, 0x00FFFF, 14400, 5);


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
  myLarsonScanner.clear();
  myLarsonScanner.loop();
  myLarsonScanner2.loop();
  myLarsonScanner3.loop();
  myLarsonScanner4.loop();
  myLarsonScanner5.loop();
  FastLED.show();
}
