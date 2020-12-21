// This supresses the pragma version warning FASTLED produces
#define FASTLED_INTERNAL
#include <FastLED.h>
#include "twinkleLights.h"
#include "larsonScanner.h"
#include "pleaseWait.h"
#include "chaseLights.h"
#include "timer.h"
#include "flicker.h"

boolean debug = false;

// WS2812B LED Data Pin
const int ledPin = 7;

unsigned char brightness = 60;

#define NUM_LEDS 22
CRGB leds[NUM_LEDS];

// Christmas Colors
CRGB colors[] = { 0xFF0000, 0x00FF00, 0x0000FF, 0xFFFF00 };
unsigned char numColors = sizeof(colors) / sizeof(CRGB);
//twinkleLights  myChristmasLights(&leds[0], NUM_LEDS,
//                                 &colors[0], numColors);
boolean christmasOn = false;

//pleaseWait myPleaseWait(&leds[0], NUM_LEDS,
//                        5, 2.5, 0x00FFFF);
//
larsonScanner myLarsonScanner(&leds[0], NUM_LEDS, 0xFF0000, 5500, 1);
//larsonScanner myLarsonScanner2(&leds[0], NUM_LEDS, 0x00FF00, 6600, 1);
//larsonScanner myLarsonScanner3(&leds[0], NUM_LEDS, 0x0000FF, 7700, 1);
//larsonScanner myLarsonScanner4(&leds[0], NUM_LEDS, 0xFF00FF, 8800, 1);
//larsonScanner myLarsonScanner5(&leds[0], NUM_LEDS, 0x00FFFF, 9900, 1);

chaseLights myChaseLights(&leds[0], NUM_LEDS, 0xFF6519, 1500);

timer myTimer(&leds[0], NUM_LEDS, 10, 0x00FF00, 0xFF0000);

flicker f1(&leds[0], 9, 0xE25822);
flicker f2(&leds[9], 9, 0xFF0000,250,250);
//flicker f3(&leds[4], 4, 0x0000FF);

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

  //  myPleaseWait.start();
//  myTimer.start();
}

void loop() {
  // put your main code here, to run repeatedly:
  //  myChristmasLights.loop();
//      myLarsonScanner.clear();
//      myLarsonScanner.loop();
  //  myLarsonScanner2.loop();
  //  myLarsonScanner3.loop();
  //  myLarsonScanner4.loop();
  //  myLarsonScanner5.loop();
//  myTimer.clear();
//  myTimer.loop();
//  if (myTimer.isStopped()) {
//    myTimer.setDuration(120);
//    myTimer.start();
//  }
//  myChaseLights.loop();
  f1.loop();
  f2.loop();
//  f3.loop();

  FastLED.show();
}
