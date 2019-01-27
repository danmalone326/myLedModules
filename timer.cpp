// -----
// timer.cpp - Library for displaying a countdown timer.
// This class is implemented for use with the Arduino environment.
// Copyright (c) by Dan Malone
// This work is licensed under a BSD style license.
// More information on:
// -----
// 01/26/2019 Initial code
// -----

#include "timer.h"

// This supresses the pragma version warning FASTLED produces
#define FASTLED_INTERNAL
#include <FastLED.h>

CRGB timer::lerpColor(CRGB fromColor, CRGB toColor, float percent) {
  CRGB result;
  unsigned char fract8 = (int)(255 * percent);

  result.r = lerp8by8(fromColor.r, toColor.r, fract8);
  result.g = lerp8by8(fromColor.g, toColor.g, fract8);
  result.b = lerp8by8(fromColor.b, toColor.b, fract8);

  return result;
}

timer::timer (struct CRGB *_leds,
              unsigned int _numLeds,
              unsigned int _durationSeconds,
              CRGB _startColor,
              CRGB _endColor) {
  leds = _leds;
  numLeds = _numLeds;
  duration = (unsigned long)_durationSeconds * 1000;
  startColor = _startColor;
  endColor = _endColor;
  on = false;
}

void timer::setDuration(unsigned int _durationSeconds) {
  duration = (unsigned long)_durationSeconds * 1000;
}

void timer::setStartColor(CRGB _startColor) {
  startColor = _startColor;
}

void timer::setEndColor(CRGB _endColor) {
  endColor = _endColor;
}

void timer::start() {
  startTime = millis();
  on = true;
}

void timer::stop() {
  on = false;
}

boolean timer::isStopped()
{
  return !on;
}

void timer::clear() {
  unsigned char counter;
  for (counter = 0; counter < numLeds; counter++) {
    leds[counter] = 0x000000;
  }
}

void timer::loop()
{
  unsigned int fadeOverlap = 1;
  float percentRemaining = (duration - (float)(millis() - startTime)) / duration;
  CRGB color;
  int i;
  float ledMin;
  float ledMax;
  float ledPercent;

  if (on) {
    if (percentRemaining <= 0) {
      stop();
    } else {
      color = lerpColor(endColor, startColor, percentRemaining);
      ledMin = (percentRemaining * numLeds) - fadeOverlap;
      ledMax = (percentRemaining * numLeds) + fadeOverlap;
      for (i = 0; i < numLeds; i++) {
        if (i > ledMax) {
          ledPercent = 0.0;
        } else if (i < ledMin) {
          ledPercent = 1.0;
        } else {
          ledPercent =  1.0 - (float)(i - ledMin) / (ledMax - ledMin);
        }
        leds[i] = lerpColor(leds[i], color, ledPercent);
      }
    }
  }
}
