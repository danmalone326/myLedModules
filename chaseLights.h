// -----
// chaseLights.h - Library for displaying a Star Trek style chase lights.
// This class is implemented for use with the Arduino environment.
// Copyright (c) by Dan Malone
// This work is licensed under a BSD style license.
// More information on:
// -----
// 01/20/2019 Initial code
// -----

#ifndef chaseLights_h
#define chaseLights_h

#include "Arduino.h"

// This supresses the pragma version warning FASTLED produces
#define FASTLED_INTERNAL
#include <FastLED.h>

class chaseLights {
  public:
    chaseLights (struct CRGB *_leds,
                   unsigned int _numLeds,
                   CRGB _color,
                   unsigned long _millisPerScan = 2000);
 
    void restartScan (unsigned long _startOfScanMillis = millis());
    void clear();
    void loop();
 
  private:
    CRGB *leds;
    unsigned int numLeds = 0;
    unsigned int halfNumLeds = 0;
    unsigned int leftStartLed = 0;
    unsigned int rightStartLed = 0;
    CRGB color;
    unsigned long millisPerScan = 0;
    unsigned long startOfScanMillis = 0;
};

#endif
