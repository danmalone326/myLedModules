// -----
// chaseLights.cpp - Library for displaying a Star Trek style chase lights.
// This class is implemented for use with the Arduino environment.
// Copyright (c) by Dan Malone
// This work is licensed under a BSD style license.
// More information on:
// -----
// 01/20/2019 Initial code
// -----

#include "chaseLights.h"

chaseLights::chaseLights (struct CRGB *_leds,
                          unsigned int _numLeds,
                          CRGB _color,
                          unsigned long _millisPerScan = 2000) {
  leds = _leds;
  numLeds = _numLeds;
  color = _color;
  millisPerScan = _millisPerScan;

  halfNumLeds = ceil(numLeds / 2.0);
  leftStartLed = halfNumLeds - 1;
  rightStartLed = numLeds - halfNumLeds;
}

void chaseLights::restartScan (unsigned long _startOfScanMillis = millis()) {
  startOfScanMillis = _startOfScanMillis;
}

void chaseLights::clear() {
  unsigned char counter;
  for (counter = 0; counter < numLeds; counter++) {
    leds[counter] = 0x000000;
  }
}

void chaseLights::loop() {
  unsigned long millisThisLoop = millis();
  unsigned int thisLed;

  if (millisThisLoop >= (startOfScanMillis + millisPerScan)) {
    restartScan(millisThisLoop);
  } else {
    thisLed = (int)floor((millisThisLoop - startOfScanMillis) / (millisPerScan / halfNumLeds)) % halfNumLeds;
    leds[leftStartLed - thisLed] = color;
    leds[rightStartLed + thisLed] = color;
  }
}
