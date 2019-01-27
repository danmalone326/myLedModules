// -----
// larsonScanner.h - Library for displaying a Larson Scanner
// This class is implemented for use with the Arduino environment.
// Copyright (c) by Dan Malone
// This work is licensed under a BSD style license.
// More information on:
// -----
// 01/20/2019 Initial code
// -----

#ifndef larsonScanner_h
#define larsonScanner_h

#include "Arduino.h"

// This supresses the pragma version warning FASTLED produces
#define FASTLED_INTERNAL
#include <FastLED.h>

class larsonScanner {
  public:
    larsonScanner (struct CRGB *_leds,
                   unsigned int _numLeds,
                   CRGB _color,
                   unsigned long _millisPerScan = 2000,
                   unsigned char _scanWidth = 3);
 
    void restartScan (unsigned long _startOfScanMillis = millis());
    void clear();
    void loop();
 
  private:
    CRGB *leds;
    unsigned int numLeds = 0;

    CRGB color;

    unsigned long millisPerScan = 0;
    unsigned long startOfScanMillis = 0;
    unsigned long endOfScanMillis = 0;
    unsigned char scanWidth = 0;

    CRGB lerpColor(CRGB fromColor, CRGB toColor, float percent);
};

#endif
