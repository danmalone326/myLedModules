// -----
// flicker.h - Library for displaying a flicker like a candle or fireplace
// This class is implemented for use with the Arduino environment.
// Copyright (c) by Dan Malone
// This work is licensed under a BSD style license.
// More information on:
// -----
// 11/28/2019 Initial code
// -----

#ifndef flicker_h
#define flicker_h

#include "Arduino.h"

// This supresses the pragma version warning FASTLED produces
#define FASTLED_INTERNAL
#include <FastLED.h>

class flicker {
  public:
    flicker (struct CRGB *_leds,
             unsigned int _numLeds,
             CRGB _color,
             unsigned long _millisPerCycle = 72,
             unsigned long _millisToTarget = 0);
 
    void clear();
    void loop();
 
  private:
    CRGB *leds;
    unsigned int numLeds = 0;

    CRGB color;
    float previousPercent = 0.0;
    float targetPercent = 0.0;

    unsigned long millisPerCycle = 72;
    unsigned long millisLastCycle = 0;
    unsigned long millisToTarget = 0;

};

#endif
