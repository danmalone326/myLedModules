// -----
// flicker.cpp - Library for displaying a flicker like a candle or fireplace
// This class is implemented for use with the Arduino environment.
// Copyright (c) by Dan Malone
// This work is licensed under a BSD style license.
// More information on:
// -----
// 11/28/2019 Initial code
// -----

#include "flicker.h"

flicker::flicker (struct CRGB *_leds,
                 unsigned int _numLeds,
                 CRGB _color,
                 unsigned long _millisPerCycle = 72,
                 unsigned long _millisToTarget = 0) {
  leds = _leds;
  numLeds = _numLeds;
  color = _color;
  millisPerCycle = _millisPerCycle;
  millisToTarget = _millisToTarget;
}

void flicker::clear() {
  unsigned char counter;
  for (counter = 0; counter < numLeds; counter++) {
    leds[counter] = 0x000000;
  }
}

const int dimSteps = 24;
const float dimPercentLow = 0.3125;
const float dimPercentStepDelta = (1.0-dimPercentLow)/dimSteps;

void flicker::loop() {
  float currentMillis = millis();
  float transitionPercent;
  float dimPercent;
  CRGB currentDim;

  if (currentMillis - millisLastCycle > millisPerCycle) {
    millisLastCycle = currentMillis;
  
    previousPercent = targetPercent;
    if (random(2) == 0) {
      targetPercent = 1;
    } 
    else {
      targetPercent = (random(dimSteps)*dimPercentStepDelta)+dimPercentLow;
    }
 
  } else {

    if (currentMillis - millisLastCycle > millisToTarget) {
      transitionPercent = 1;
    } else {
      transitionPercent = (currentMillis - millisLastCycle) / millisToTarget;
    }

    dimPercent = previousPercent + ((targetPercent - previousPercent) * transitionPercent);
    
    currentDim = color;
    currentDim.fadeLightBy(255-int(255*dimPercent));
    for (int ledNum = 0; ledNum < numLeds; ledNum++) {
      leds[ledNum] = currentDim;
    }
  }
}

//    float previousPercent = 0.0;
//    float targetPercent = 0.0;
//
//    unsigned long millisPerCycle = 72;
//    unsigned long millisLastCycle = 0;
//    unsigned long millisToTarget = 0;
