// -----
// timer.h - Library for displaying a countdown timer.
// This class is implemented for use with the Arduino environment.
// Copyright (c) by Dan Malone
// This work is licensed under a BSD style license.
// More information on:
// -----
// 01/26/2019 Initial code
// -----

#ifndef timer_h
#define timer_h

#include "Arduino.h"

// This supresses the pragma version warning FASTLED produces
#define FASTLED_INTERNAL
#include <FastLED.h>

class timer {
  public:
    timer (struct CRGB *_leds,
           unsigned int _numLeds,
           unsigned int _durationSeconds,
           CRGB _startColor,
           CRGB _endColor);

    void setDuration(unsigned int _durationSeconds);
    void setStartColor(CRGB _startColor);
    void setEndColor(CRGB _endColor);
    void start();
    void stop();
    boolean isStopped();
    void clear();
    void loop();

  private:
    CRGB *leds;
    unsigned int numLeds = 0;
    unsigned long duration = 0;
    unsigned long startTime = 0;
    CRGB startColor;
    CRGB endColor;
    boolean on;
    CRGB lerpColor(CRGB fromColor, CRGB toColor, float percent);
};

#endif
